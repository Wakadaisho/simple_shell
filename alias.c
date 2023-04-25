#include "main.h"

/**
 * _aliases - get/set aliases from anywhere, statically
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
char **_aliases(char **args, int mode)
{
	static char **aliases;
	int len = 0, i = 0;

	if (args == NULL && mode == SEED)
	{
		aliases = malloc(2 * sizeof(char *));
		aliases[0] = NULL;
		aliases[1] = NULL;
		return (aliases);
	}

	if (mode == FREE)
	{
		_freeTokenized(aliases);
		return (NULL);
	}

	if (mode == READ)
	{
		return (aliases);
	}
	
	if (args)
	{
		while (args[len])
			len++;
		_freeTokenized(aliases);
		aliases = malloc((len + 1) * sizeof(char *));

		for (i = 0; i < len; i++)
			aliases[i] = _strdup(args[i]);
		aliases[i] = NULL;
		if (mode != SEED )
			_freeTokenized(args);
	}
	return (aliases);
}

/**
 * listAliases - print out aliases to stdout
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
int listAliases(char **args)
{
	int i = 0, j = 0, len = 0;
	char **aliases = _aliases(NULL, READ);
	char **kv;
	char **var, **var_cpy;

	if (aliases == NULL)
		return (1);
	
	if (args[1] == NULL)
	{
		for (i = 0; aliases[i]; i++)
		{
			write(STDOUT_FILENO, aliases[i], _strlen(aliases[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	for (i = 0; aliases[i]; i++)
	{
		kv = tokenize(aliases[i], "=");
		for (j = 1; args[j]; j++)
		{
			if (_strcmp(args[j], kv[0])==0)
			{
				write(STDOUT_FILENO, aliases[i], _strlen(aliases[i]));
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
		}
		_freeTokenized(kv);
	}
	return (1);
}

/*
 * bi_alias - insert/update an alias
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_alias(char **args)
{
	int i = 0, k = 0;
	char **aliases, **aliases_cpy, **kv, **kv_a;
	int set = 0;

	if (args[1] == NULL || _strcontains(args[1], "=") == -1)
		return listAliases(args);
	
	for (k = 1; args[k]; k++, set -= set)
	{
		aliases = _aliases(NULL, READ);
		kv = tokenize(args[k], "=");
		for (i =0; aliases[i]; i++)
		{
			kv_a = tokenize(aliases[i], "=");
			if (_strcmp(kv[0], kv_a[0]) == 0)
			{
				free(aliases[i]);
				_freeTokenized(kv_a);
				aliases[i] = _strdup(args[k]);
				set = 1;
				break;
			}
			_freeTokenized(kv_a);
		}
		
		if (set)
			continue;

		aliases_cpy = malloc((i + 2) * sizeof(char *));
		for (i = 0; aliases && aliases[i]; i++)
			aliases_cpy[i] = _strdup(aliases[i]);
		aliases_cpy[i++] = _strdup(args[k]);
		aliases_cpy[i] = NULL;
		_aliases(aliases_cpy, WRITE);
	}
	return (1);
}
