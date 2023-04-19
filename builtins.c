#include "main.h"

/**
 * bi_exit - exit the shell
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_exit(char **args)
{
	int ret = 0;

	if (args[1])
		ret = _atoi(args[1]);
	_environ(NULL, 1);
	exit(ret);
}

/**
 * bi_cd - change current working directory
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_cd(char **args)
{
	int size = 255, ret;
	static int firstRun = 1;
	char *cwd;
	static char *pwd;

	cwd = malloc(size * sizeof(char));

	for (; getcwd(cwd, size) == NULL; size *= 1.5)
		cwd = _realloc(pwd, size, size * 1.5);

	if (firstRun && --firstRun)
		pwd = NULL;

	if (args[1])
	{
		if (_strcmp(args[1], "-") == 0)
		{
			ret = chdir(pwd == NULL ? cwd : pwd);
		}
		else
		{
			ret = chdir(args[1]);
		}
		if (pwd)
			free(pwd);
		pwd = cwd;
		return (ret);
	}
	ret = chdir(_getenv("HOME"));
	if (pwd)
		free(pwd);
	pwd = cwd;
	return (ret);
}
