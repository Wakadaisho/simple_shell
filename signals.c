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
	write(STDOUT_FILENO, "\n($) ", 5);
	return;
	/**
	 * cleanMemory();
	 *	exit(0);
	 */
}
