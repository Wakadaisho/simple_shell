#include "main.h"

/**
 * main - simple shell environment
 *
 * @argc: number of command line arguments
 * @argv: command line arguments
 *
 * Return:	0 - success
 */
int main(int argc, char **argv)
{
	if (!isatty(fileno(stdin)))
	{
		repl();
		return (0);
	}

	while (1)
	{
		/*Display prompt*/
		write(STDOUT_FILENO, "($) ", 4);

		repl();
	}

	return (0);
}
