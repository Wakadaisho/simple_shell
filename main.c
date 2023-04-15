#include "main.h"

/**
 * main - simple shell environment
 *
 * @argc: number of command line arguments
 * @argv: command line arguments
 * @env: environment variables
 *
 * Return:	0 - success
 */
int main(int argc, char **argv, char **env)
{
	_environ(env, 0);

	if (!isatty(fileno(stdin)))
	{
		repl();
		_environ(NULL, 1);
		return (0);
	}

	while (1)
	{
		/*Display prompt*/
		write(STDOUT_FILENO, "($) ", 4);

		repl();
	}

	_environ(NULL, 1);
	return (0);
}
