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
	int n = 10, len = 0;
	char *str, *p, *token = NULL;
	char **tokens;

	if (s == NULL)
		return (NULL);

	tokens = malloc(n * sizeof(char *));

	if (tokens == NULL)
		return (NULL);

	p = str = _strdup(s);
	if (p == NULL)
		return (NULL);
	token = _strdup(_strtok_r(str, delims, &str));

	while (token)
	{
		if (len >= n) /* TO_DO: Realloc if tokens is full */
		{
			tokens = _reallocp(tokens, n, n * 1.5);
			n *= 1.5;
			if (tokens == NULL)
			{
				free(p);
				return (NULL);
			}
		}
		tokens[len++] = token;
		token = _strdup(_strtok_r(NULL, delims, &str));
	}
	free(p);
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
 * stripCharacters - strip from the beginning and end of string
 *
 * @str: string to remove edge characters
 * @chars: characters to strip
 *
 * Return: pointer to new string
 */
char *stripCharacters(char *str, char *chars)
{
	char *s;
	int i = 0;
	char chrToStr[] = {'\0', '\0'};

	if (str == NULL)
		return (NULL);

	*chrToStr = *(str + i);
	/* ignore chars from front */
	while (_strcontains(chars, chrToStr) != -1)
		*chrToStr = *(str + ++i);

	s = _strdup(str + i);
	if (*s == '\0')
		return (s);

	i = _strlen(s);
	*chrToStr = *(s + i);
	/* null whitespace from back */
	while (_strcontains(chars, chrToStr) != -1)
	{
		*(s + i) = '\0';
		*chrToStr = *(s + --i);
	}

	return (s);
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
