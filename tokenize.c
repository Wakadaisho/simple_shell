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
	int size = 10;
	int len = 0;
	const char *default_delims = " \t";
	char *token = NULL;
	char **tokens = malloc(10 * sizeof(char *));

	if (tokens == NULL)
		return (NULL);

	if (delims == NULL)
		delims = default_delims;

	token = strtok(s, delims);

	while (token)
	{
		/* TO_DO: Realloc if tokens is full */
		tokens[len++] = token;

		token = strtok(NULL, delims);
	}

	tokens[len] = NULL;

	return (tokens);
}
