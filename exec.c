#include <sys/wait.h>
#include <errno.h>
#include "main.h"

/**
 * continueChain - determine whether to continue executing
 *			a chained command
 * @op: logical operator or ';'
 * @errorCode: last error code
 *
 * Return:	1 for true
 *		0 for false
 */
int continueChain(char *op, int errorCode)
{
	int op_val = 0;

	if (op == NULL)
		return (1);
	op_val += _strcontains(op, "&&") ? 0 : 1 << 2;
	op_val += _strcontains(op, "||") ? 0 : 1 < 1;
	op_val += _strcontains(op, ";") ? 0 : 1 << 0;

	switch (op_val)
	{
		case 4:			/* && */
			return (!errorCode);
		case 2:			/* || */
			return (errorCode);
		case 1:			/* ; */
			return (1);
		default:
			return (0);
	}
}

/**
 * executeCommand - run a command in the shell
 *
 * @args: pointer to a vector of C strings,
 *		ending with a NULL pointer
 *
 * Return: void
 */
void executeCommand(char **args)
{
	int wstatus;
	char *cmd, *tmp;
	pid_t proc;

	/*check if builtin command and execute*/
	execBuiltin(args);
	if (accessErrorCode(0, READ) == 1)
	{
		accessErrorCode(0, WRITE);
		return;
	}
	tmp = stripCharacters(args[0], " \r\t");
	if (_strlen(tmp) == 0)
	{
		free(tmp);
		accessErrorCode(0, WRITE);
		return;
	}
	if (accessErrorCode(0, READ) != 0)
		return;
	cmd = getCmdPath(tmp);
	free(tmp);
	if (cmd == NULL || accessErrorCode(0, READ) != 0)
		return;
	proc = fork();
	if (proc == 0)
	{
		execve(cmd, args, _environ(NULL, READ));
	}
	else if (proc > 0)
	{
		wait(&wstatus);
	}
	else
	{
	accessErrorCode(127, WRITE);
		return;
	}
	free(cmd);
	accessErrorCode(WEXITSTATUS(wstatus), WRITE);
}

/**
 * repl - describe a transaction of:
 *		1. Taking input from the user
 *		2. Executing said input
 *		3. Printing any output
 *
 * @argv: arguments passed to main
 *
 * Return: void
 */
void repl(char **argv)
{
	char *cmd, *alias = NULL, *tmp, **tokens = NULL, ***cmds = NULL;
	int errorCode = 0, i = 0, k = 0;

	cmd = getInput();
	if (cmd == NULL)
		return;
	filterComment(cmd, "#");
	tmp = _strsubstitute(cmd, "\n", " ; ");
	free(cmd);
	cmds = _accesscmds(tokenizeCommand(tmp), WRITE);
	free(tmp);
	for (i = 0; cmds[0][i]; i++)
	{
		alias = _getalias(cmds[0][i]);
		if (alias)
		{
			tokens = tokenize(alias, " \t\n");
			free(alias);
		}
		else
		{
			tokens = tokenize(cmds[0][i], " \t\n");
		}
		for (k = 1; tokens[k]; k++)
		{
			tmp = stripCharacters(tokens[k], "\'\"");
			free(tokens[k]);
			tokens[k] = tmp;
		}
		parseVariables(tokens);
		executeCommand(tokens);
		errorCode = accessErrorCode(0, READ);
		printError(cmds[0][i], argv[0]);
		_freeTokenized(tokens);
		if (cmds[1] && cmds[1][i])
		{
			if (continueChain(cmds[1][i], errorCode) == 0)
				break;
		}
	}
}
