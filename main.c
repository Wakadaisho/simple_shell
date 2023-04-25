#include "main.h"
#include <signal.h>

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
	signal(SIGINT, endSignal);
	_environ(env, SEED);
	_aliases(NULL, SEED);

	if (!isatty(fileno(stdin)))
	{
		repl(argc, argv);
		getInput(FREE);
		_environ(NULL, FREE);
		return (0);
	}

	while (1)
	{
		/*Display prompt*/
		write(STDOUT_FILENO, "($) ", 4);

		repl(argc, argv);
	}

	_environ(NULL, FREE);
	return (0);
}
