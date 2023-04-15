#include <sys/wait.h>
#include "main.h"

/**
 * executeCommand - run a command in the shell
 *
 * @args: pointer to a vector of C strings,
 *		ending with a NULL pointer
 *
 * Return: execve return value
 */
int executeCommand(char **args)
{
	int ret, status, i = 0;
	char **aliases = NULL;

	char *cmd = args[0];

	cmd = getCmdPath(cmd);

	if (cmd == NULL)
	{
		perror("hsh");
		return (-1);
	}

	pid_t proc = fork();

	if (proc == 0)
	{
		ret = execve(cmd, args, aliases);
		perror(cmd);
		exit(1);
	}
	else if (proc > 0)
	{
		do {
			waitpid(proc, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	} else
	{
		perror("hsh");
	}

	return (ret);
}

/**
 * repl - describe a transaction of:
 *		1. Taking input from the user
 *		2. Executing said input
 *		3. Printing any output
 *
 * Return: void
 */
void repl(void)
{
	char *cmd = NULL;
	char **tokens =  NULL;

	/*Get user input*/
	cmd = getInput();

	filterComment(cmd, "#");

	if (_strlen(cmd) == 0)
		return;

	/*Tokenize input*/
	tokens = tokenize(cmd, NULL);

	/*Execute command*/
	executeCommand(tokens);

	/*Free memory allocations tokenize*/
	if (tokens)
	{
		if (tokens[0])
			free(tokens[0]);
		free(tokens);
	}

	free(cmd);
}
