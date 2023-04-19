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
	int ret;

	ret = getline(&cmd, &size, stdin);
	if (ret == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(cmd);
		_environ(NULL, 1);
		exit(0);
	}

	return (cmd);
}
