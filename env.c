#include <sys/stat.h>
#include "main.h"

/**
 * _environ - get environment variables from anywhere, statically
 *
 * @env:	environment variables to store, NULL to reuse stored
 * @mode:	0 - default, ovewrites environ to env if exists
 *		1 - free environ then quit (ignores env)
 *
 * Return:	pointer to environment variable strings
 *		NULL if environment not previously given
 */
char **_environ(char **env, int mode)
{
	static char **environ;
	int len = 0, i = 0;

	if (mode == 1)
	{
		_freeTokenized(environ);
		return (NULL);
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
	char **env = _environ(NULL, 0);
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
 * getCmdPath - check whether a command exist in another path
 *		and return that path
 *
 * @cmd: command to check in the PATH variable
 * @error:	error code of command search
 *		0 - found command
 *		-1 - could not find file/directory
 *		-2 - command doesn't exist
 *
 * Return:	new path if exists
 *		NULL if path does not exist
 */
char *getCmdPath(char *cmd, int *error)
{
	int i = 0;
	char *path;
	char **paths;
	char *location = NULL;
	struct stat st;

	*error = 0;

	if (cmd == NULL || *cmd == '\0')
		return (NULL);

	if (_strcontains(cmd, "/") != -1)
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		*error = -2;
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

	*error = -3;
	free(path);
	_freeTokenized(paths);
	return (NULL);
}
