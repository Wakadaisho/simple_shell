#include "main.h"

/**
 * endSignal - clean the static environment variable
 *
 * @sig: signal received
 *
 * Return: void
 */
void endSignal(int sig)
{
	char **cd_free = malloc(sizeof(char *));

	cd_free[0] = NULL;
	write(STDOUT_FILENO, "\n", 1);
	_environ(NULL, FREE);
	bi_cd(cd_free);
	free(cd_free);
	getInput(FREE);
	exit(0);
}
