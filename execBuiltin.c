#include "main.h"

/**
 * execBuiltin - execute a command if it is a builtin
 *
 * @args: command typed to shell
 *
 * Return: void
 */
void execBuiltin(char **args)
{
	int (*f)(char **) = NULL;

	if (args && args[0])
		f = getBuiltin(args[0]);

	f ? accessErrorCode(f(args), WRITE) : accessErrorCode(0, WRITE);
}

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
		{"env", bi_env},
		{"exit", bi_exit},
		{"cd", bi_cd},
		{"unsetenv", bi_unsetenv},
		{"setenv", bi_setenv},
		{"alias", bi_alias},
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
