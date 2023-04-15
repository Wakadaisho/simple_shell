#include "main.h"

/**
 * tokenize - split a string into an array of strings
 *		based on certain DELIMS (delimiters)
 * @s: string to split
 * @delims: string characters to tokenize by
 *		defaults to ' ' and '\t' if NULL
 *
 * Return: array of strings, NULL if failed or no s is NULL
 */
char **tokenize(char *s, char *delims)
{
	int n = 10 * sizeof(char *);
	int len = 0;
	char *default_delims = " \t\n";
	char *token = NULL, *str;
	char **tokens = malloc(n);

	str = _strdup(s);

	if (tokens == NULL || str == NULL)
		return (NULL);

	if (delims == NULL)
		delims = default_delims;

	token = _strtok_r(str, delims, &str);

	while (token)
	{
		/* TO_DO: Realloc if tokens is full */
		if (len >= n)
		{
			tokens = (char **)_realloc((void **)tokens, n, 2 * n);
			if (tokens == NULL)
			{
				free(str);
				return (NULL);
			}
			n *= 2;
		}

		tokens[len++] = token;

		token = _strtok_r(NULL, delims, &str);
	}

	tokens[len] = NULL;

	return (tokens);
}
