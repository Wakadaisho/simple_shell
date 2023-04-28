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
	sig = sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
