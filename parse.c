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
	int n = 5 * sizeof(char *);
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
			tokens = (char **)_reallocp((void **)tokens, n, 1.5 * n);
			if (tokens == NULL)
			{
				free(str);
				return (NULL);
			}
			n *= 1.5;
		}

		tokens[len++] = token;

		token = _strtok_r(NULL, delims, &str);
	}

	tokens[len] = NULL;

	return (tokens);
}

/**
 * filterComment - find an indicator in the command and end the string there
 *
 * @s: command to check for comment indicator
 * @indicator: indicator that signifies a comment e.g. "#"
 *
 * Return: void
 */
void filterComment(char *s, char *indicator)
{
	int foundComment;

	if (s == NULL)
		return;

	foundComment = _strcontains(s, indicator);

	if (foundComment != -1)
		s[foundComment] = '\0';
}

/**
 * _strsubstitute - replace occurrences of a subtring with a string
 *
 * @str: original string
 * @sub: substring to replace
 * @rep: strint to replace substring by
 *
 * Return:	pointer to new string
 *		NULL on failure
 */
char *_strsubstitute(char *str, char *sub, char *rep)
{
	int pos, i, lr = _strlen(rep), ls = _strlen(sub), delta = lr - ls;
	char *tmp, *s = _strdup(str);

	if (lr == 0)
		rep = "";

	if (ls == 0)
		return (s);

	for (pos = _strcontains(s, sub); pos != -1;)
	{
		tmp = malloc(_strlen(s) + delta + 1);
		for (i = 0; i < pos; i++)			/*copy string to pos*/
			tmp[i] = s[i];
		for (i = 0; i < lr; i++)			/*add replacement*/
			tmp[pos + i] = rep[i];
		for (i = pos; *(s + ls + i); i++)		/*copy rest of string*/
			tmp[i + lr] = s[i + ls];
		tmp[i + lr] = '\0';
		free(s);
		s = tmp;
		pos = _strcontains(s, sub);
	}

	return (s);
}
