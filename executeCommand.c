#include <sys/wait.h>
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
	int ret, status;
	pid_t proc = fork();

	if (proc == 0)
	{
		ret = execve(args[0], args, NULL);
		perror("hsh");
		exit(1);
	}
	else if (proc > 0)
	{
		do {
			waitpid(proc, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	} else
	{
		perror("hsh");
	}

	return (ret);
}
