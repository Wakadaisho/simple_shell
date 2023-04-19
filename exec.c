#include <sys/wait.h>
#include <errno.h>
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
	int wstatus, i = 0, error = 0;
	char *cmd, *tmp;
	int builtin;

	tmp = stripWhitespace(args[0]);

	if (_strlen(tmp) == 0)
	{
		free(tmp);
		return (0);
	}

	/*check if builtin command and execute*/
	builtin = execBuiltin(args);

	cmd = getCmdPath(tmp, &error);
	free(tmp);

	if (cmd == NULL || error < 0)
	{
		return (error);
	}
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
		return (127);
	}

	free(cmd);
	return (WEXITSTATUS(wstatus));
}

/**
 * printError - print out an error that occured based on a code
 * @cmd: command that caused the error
 * @shell: name of shell application
 * @errorCode: error code
 *
 * Return: void
 */
void printError(char *cmd, char *shell, int errorCode)
{
	char *cmdshell = _strjoin(shell, cmd, ": ");
	char *error = NULL;

	switch (errorCode)
	{
		case 0:
			break;
		case -2:
			error = _strjoin(shell, "No such file or directory\n", ": ");
			break;
		case -3:
			error = _strjoin(cmdshell, "command not found\n", ": ");
			break;
		default:
			perror(shell);
	}

	write(STDERR_FILENO, error, _strlen(error));
	if (error)
		free(error);
	free(cmdshell);
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
	cmd = getInput();

	filterComment(cmd, "#");

	if (_strlen(cmd) == 0)
	{
		if (cmd != NULL)
			free(cmd);
		return;
	}

	/*Tokenize input*/
	tokens = tokenize(cmd, " \t\n");

	/*Execute command*/
	errorCode = executeCommand(tokens);
	/*
	 * printError(cmd, argv[0], errorCode);
	 */

	/*Free memory allocations*/
	_freeTokenized(tokens);
	free(cmd);
}
