#include <sys/wait.h>
#include <errno.h>
#include "main.h"

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
	int wstatus, i = 0;
	char *cmd, *tmp;

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

	if (cmd == NULL || accessErrorCode(0, READ) < 0)
		return;

	pid_t proc = fork();

	if (proc == 0)
	{
		execve(cmd, args, NULL);
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
 * @argc: number of arguments passed to main
 * @argv: arguments passed to main
 *
 * Return: void
 */
void repl(int argc, char **argv)
{
	char *cmd = NULL;
	char **tokens =  NULL;
	int errorCode, i = 0;

	/*Get user input*/
	cmd = getInput(READ);

	filterComment(cmd, "#");

	if (_strlen(cmd) == 0)
		return;

	/* separate command by logic operators*/

	/* for each separated command*/

	/*Tokenize input*/
	tokens = tokenize(cmd, " \t\n");

	/*if alias, exex alias*/

	/*Execute command*/
	executeCommand(tokens);
	
	printError(cmd, argv[0]);

	/*Free memory allocations*/
	_freeTokenized(tokens);
}

/**
 * execBuiltin - execute a command if it is a builtin
 *
 * @args: command typed to shell
 *
 * Return: void
 */
void execBuiltin(char **args)
{
	int (*f)(char **) = NULL;

	if (args && args[0])
		f = getBuiltin(args[0]);

	f ? accessErrorCode(f(args), WRITE) : accessErrorCode(0, WRITE);
}

/**
 * getBuiltin - return a builtin function
 *
 * @cmd: command to compare to defined builtins
 *
 * Return: int (*)(char **args) - function that can be executed on args
 */
int (*getBuiltin(char *cmd))(char **args)
{
	int i = 0;
	bi_t builtins[] = {
		{"exit", bi_exit},
		{"cd", bi_cd},
		{"env", bi_env},
		{"unsetenv", bi_unsetenv},
		{"setenv", bi_setenv},
		{"alias", bi_alias},
		{NULL, NULL},
	};

	while (builtins[i].name)
	{
		if (_strcmp(builtins[i].name, cmd) == 0)
			return (builtins[i].f);
		i++;
	}
	return (NULL);
}
