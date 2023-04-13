#include "main.h"

/**
 * getInput - get string input from the user
 *
 * Return: pointer to string input
 */
char *getInput(void)
{
	char *cmd = NULL;
	size_t size = 0;

	if (getline(&cmd, &size, stdin) == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(cmd);
		exit(0);
	}

	return (cmd);
}
