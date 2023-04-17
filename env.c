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
		if (environ)
		{
			while (environ[i])
				free(environ[i++]);
			free(environ);
		}
		return (NULL);
	}

	if (env)
	{
		while (env[len])
			len++;
		if (environ)
		{
			while (environ[i])
				free(environ[i++]);
			free(environ);
		}
		environ = malloc((len + 1) * sizeof(char *));
		i = 0;
		while (i < len)
		{
			environ[i] = _strdup(env[i]);
			i++;
		}
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
	char **var;
	char **env = _environ(NULL, 0);

	while (env[i])
	{
		var = tokenize(env[i++], "=");
		if (_strcmp(var[0], name) == 0)
			return (var[1]);
		free(var);
	}

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
	char *path = _getenv("PATH");
	char **paths = tokenize(path, ":");
	char *location = NULL;
	struct stat st;

	if (_strcontains(cmd, "/") != -1)
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	while (paths[i])
	{
		location = _strjoin(paths[i], cmd, "/");
		if (stat(location, &st) == 0)
			return (location);
		if (location)
			free(location);
		i++;
	}

	return (NULL);
}
