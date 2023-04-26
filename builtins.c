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
	_freeTokenized(args);
	cleanMemory();
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
	char *cwd, *home;
	static char *pwd;

	cwd = malloc(size * sizeof(char));
	for (; getcwd(cwd, size) == NULL; size *= 1.5)
		cwd = _realloc(pwd, size, size * 1.5);
	if (firstRun && --firstRun)
		pwd = NULL;
	if (args[0] == NULL)
	{
		if (pwd)
			free(pwd);
		free(cwd);
		return (1);
	}
	if (args[1] == NULL)
	{
		home = _getenv("HOME");
		ret = chdir(home);
		free(home);
		if (pwd)
			free(pwd);
		pwd = cwd;
		_setenv("PWD", cwd);
		return (ret == 0 ? 1 : -1);
	}
	ret = _strcmp(args[1], "-") ? chdir(args[1]) : chdir(pwd ? pwd : cwd);
	if (pwd)
		free(pwd);
	pwd = cwd;
	_setenv("PWD", cwd);
	return (ret == 0 ? 1 : -1);
}

/**
 * bi_setenv - insert/update an environment variable
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_setenv(char **args)
{
	int i = 0;
	char **env = _environ(NULL, READ), **env_cpy;
	char *key, *var, *var_cp;

	if (args[1] == NULL || args[2] == NULL)
		return (-1);

	for (i = 0; env[i]; i++)
	{
		var_cp = var = _strdup(env[i]);
		key = _strtok_r(var, "=", &var);
		if (_strcmp(key, args[1]) == 0)
		{
			free(env[i]);
			free(var_cp);
			env[i] = _strjoin(args[1], args[2], "=");
			return (1);
		}
		free(var_cp);
	}

	env_cpy = malloc((i + 2) * sizeof(char *));
	for (i = 0; env[i]; i++)
		env_cpy[i] = _strdup(env[i]);
	env_cpy[i++] = _strjoin(args[1], args[2], "=");
	env_cpy[i] = NULL;
	_environ(env_cpy, WRITE);
	return (1);
}

/**
 * bi_unsetenv - remove an environment variable
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_unsetenv(char **args)
{
	int i = 0, j = 0;
	char **env = _environ(NULL, READ), **env_cpy;
	char *key, *var, *var_cp;

	if (args[1] == NULL)
		return (-1);

	while (env[i++])
		continue;

	env_cpy = malloc(i * sizeof(char *));

	for (i = 0, j = 0; env[i]; i++, j++)
	{
		var_cp = var = _strdup(env[i]);
		key = _strtok_r(var, "=", &var);
		if (_strcmp(key, args[1]) == 0)
		{
			j--;
			free(var_cp);
			continue;
		}
		free(var_cp);
		env_cpy[j] = _strdup(env[i]);
	}

	env_cpy[j] = NULL;
	_environ(env_cpy, WRITE);

	return (1);
}

/**
 * bi_env - print the environment variables
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_env(char **args)
{
	int i;
	char **env = _environ(NULL, READ);

	args = args;
	for (i = 0; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (1);
}
