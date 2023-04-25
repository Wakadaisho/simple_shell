#include <sys/stat.h>
#include "main.h"

/**
 * _environ - get environment variables from anywhere, statically
 *
 * @env:	environment variables to store, NULL to reuse stored
 * @mode	-1 - initial seed (no free)
 *		0 - returns environ (ignores env)
 *		1 - sets environ, then returns it
 *		2 - free environ then quit (ignores env)
 *
 * Return:	pointer to environment variable strings
 *		NULL if environment not previously given
 */
char **_environ(char **env, int mode)
{
	static char **environ;
	int len = 0, i = 0;

	if (mode == FREE)
	{
		_freeTokenized(environ);
		return (NULL);
	}

	if (mode == READ)
	{
		return (environ);
	}
	
	if (env)
	{
		while (env[len])
			len++;
		_freeTokenized(environ);
		environ = malloc((len + 1) * sizeof(char *));

		for (i = 0; i < len; i++)
			environ[i] = _strdup(env[i]);
		environ[i] = NULL;
		if (mode != SEED )
			_freeTokenized(env);
	}
	return (environ);
}

/**
 * _getenv - get the value of an environment variable
 *
 * @name: environment variable to search for
 *
 * Return:	pointer to environment variable string
 *		NULL if not found
 */
char *_getenv(char *name)
{
	int i = 0;
	char **env = _environ(NULL, READ);
	char *key, *value;
	char *ret, *str, *p;

	while (env[i])
	{
		p = str = _strdup(env[i++]);
		key = _strdup(_strtok_r(str, "=", &str));
		value = _strdup(str);
		free(p);
		if (_strcmp(name, key) == 0)
		{
			ret = value;
			free(key);
			return (ret);
		}
		free(key);
		free(value);
	}
	_freeTokenized(env);
	return (NULL);
}

/**
 * _setenv - set the value of an environment variable
 *
 * @name: environment variable to set
 * @value: value to set it to
 *
 * Return:	pointer to environment variable string
 *		NULL on unset
 */
char *_setenv(char *name, char *value)
{
	char **args = malloc(3 * sizeof(char *));
	char *val;

	if (name == NULL)
		return (NULL);

	args[1] = _strdup(name);
	args[2] = NULL;

	if (value == NULL)
	{
		args[0] = _strdup("unsetenv");
		bi_unsetenv(args);
		_freeTokenized(args);
		return (NULL);
	}

	args[0] = _strdup("setenv");
	val = value == NULL ? _strdup("") : _strdup(value);
	bi_setenv(args);
	_freeTokenized(args);

	return (NULL);
}
/**
 * getCmdPath - check whether a command exist in another path
 *		and return that path
 *
 * @cmd: command to check in the PATH variable
 *
 * Return:	new path if exists
 *		NULL if path does not exist
 */
char *getCmdPath(char *cmd)
{
	int i = 0;
	char *path;
	char **paths;
	char *location = NULL;
	struct stat st;

	accessErrorCode(0, WRITE);

	if (cmd == NULL || *cmd == '\0')
		return (NULL);

	if (_strcontains(cmd, "/") != -1)
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		accessErrorCode(-2, WRITE);
		return (NULL);
	}

	path = _getenv("PATH");
	paths  = tokenize(path, ":");

	while (paths[i])
	{
		location = _strjoin(paths[i], cmd, "/");
		if (stat(location, &st) == 0)
		{
			free(path);
			_freeTokenized(paths);
			return (location);
		}
		if (location)
			free(location);
		i++;
	}

	accessErrorCode(-3, WRITE);
	free(path);
	_freeTokenized(paths);
	return (NULL);
}
