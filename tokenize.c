#include "main.h"

#define DELIMS (" \t\n")

/**
 * tokenize - split a string into an array of strings
 *		based on certain DELIMS (delimiters)
 * @s: string to split
 *
 * Return: array of strings, NULL if failed or no s is NULL
 */
char **tokenize(char *s)
{
	int size = 10;
	int len = 0;
	char *token = NULL;
	char **tokens = malloc(10 * sizeof(char *));

	if (tokens == NULL)
		return (NULL);

	token = strtok(s, DELIMS);

	while (token)
	{
		/* TO_DO: Realloc if tokens is full */
		tokens[len++] = token;

		token = strtok(NULL, DELIMS);
	}

	tokens[len] = NULL;

	return (tokens);
}
