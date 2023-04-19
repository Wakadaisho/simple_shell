#include "main.h"

/**
 * getBuiltin - return a builtin function
 *
 * @cmd: command to compare to defined builtins
 *
 * Return: int (*)(char **args) - function that can be executed on args
 */
int (*getBuiltin(char *cmd))(char **args)
{
	int i = 0;
	bi_t builtins[] = {
		{"exit", bi_exit},
		{"cd", bi_cd},
		{NULL, NULL},
	};

	while (builtins[i].name)
	{
		if (_strcmp(builtins[i].name, cmd) == 0)
			return (builtins[i].f);
		i++;
	}
	return (NULL);
}

/**
 * execBuiltin - execute a command if it is a builtin
 *
 * @args: command typed to shell
 *
 * Return:	1 - success;
 *		negative number on failure
 */
int execBuiltin(char **args)
{
	int (*f)(char **) = NULL;
	int error;

	if (args && args[0])
		f = getBuiltin(args[0]);

	if (f == NULL)
		return (-1);

	error = f(args);

	return (error);
}
