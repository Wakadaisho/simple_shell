#include "main.h"

/**
 * accessErrorCode - get or set error code
 *
 * @code: error code to set
 * @mode:	1 - set code
 * Return: error code set or requested
 */
int accessErrorCode(int code, int mode)
{
	static int errorCode;

	if (mode == WRITE)
		errorCode = code;

	return (errorCode);
}

/**
 * printError - print out an error that occured based on a code
 * @cmd: command that caused the error
 * @shell: name of shell application
 *
 * Return: void
 */
void printError(char *cmd, char *shell)
{
	char *cmdshell = _strjoin(shell, cmd, ": ");
	char *error = NULL;
	int errorCode = accessErrorCode(0, READ);

	if (errorCode >= 0)
	{
		free(cmdshell);
		return;
	}

	switch (errorCode)
	{
		case -2:
			error = _strjoin(cmdshell, "No such file or directory\n", ": ");
			break;
		case -3:
			error = _strjoin(cmdshell, "command not found\n", ": ");
			break;
		default:
			perror(shell);
			free(cmdshell);
			return;
	}

	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	free(cmdshell);
}
