#include "main.h"

/**
 * _aliases - get/set aliases from anywhere, statically
 *
 * @args:	alias to store, NULL to reuse stored
 * @mode:	-1 - initial seed (no free)
 *		0 - returns aliases (ignores args)
 *		1 - sets aliases, then returns it
 *		2 - free aliases then quit (ignores env)
 *
 * Return:	pointer to aliases strings
 *		NULL if args not previously given
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
		if (mode != SEED)
			_freeTokenized(args);
	}
	return (aliases);
}

/**
 * _getalias - get the value of an alias
 *
 * @name: alias to search for
 *
 * Return:	pointer to alias string
 *		NULL if not found
 */
char *_getalias(char *name)
{
	int i = 0;
	char **env = _aliases(NULL, READ);
	char *key, *value;
	char *ret = NULL, *str, *p;
	char chrToStr[] = {'\0', '\0'};

	while (env[i])
	{
		p = str = _strdup(env[i++]);
		key = _strdup(_strtok_r(str, "=", &str));
		value = _strdup(str);
		free(p);
		if (_strcmp(name, key) == 0)
		{
			if (*value == '"' || *value == '\'')
			{
				chrToStr[0] = *value;
				ret = stripCharacters(value, chrToStr);
				free(value);
				free(key);
				return (ret);
			}
			ret = value;
			free(key);
			return (ret);
		}
		free(key);
		free(value);
	}
	return (NULL);
}

/**
 * listAliases - print out aliases to stdout
 *
 * @args:	aliases to store, NULL to reuse stored
 *
 * Return:	pointer to alias strings
 *		NULL if aliases not previously given
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
			if (_strcmp(args[j], kv[0]) == 0)
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

/**
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
	char **aliases = NULL, **aliases_cpy, **kv = NULL, **kv_a = NULL;
	int set = 0;

	if (args[1] == NULL || _strcontains(args[1], "=") == -1)
		return (listAliases(args));
	for (k = 1; args[k]; k++, set ^= set)
	{
		aliases = _aliases(NULL, READ);
		kv = tokenize(args[k], "=");
		for (i = 0; aliases[i]; i++)
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
		_freeTokenized(kv);
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
