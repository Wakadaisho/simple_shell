#include "main.h"

/**
 * _strjoin - joins two strings, with an optional joining string
 *		returning a new pointer to string
 * @a: first string
 * @b: second string
 * @j: optional jointer string
 *
 * Return: pointer to new string
 */
char *_strjoin(char *a, char *b, char *j)
{
	int i;
	int len_a = _strlen(a);
	int len_b = _strlen(b);
	int len_j = _strlen(j);
	char *s, *p;

	s = p = malloc(len_a + len_b + len_j + 1);

	while (a && *a)
	{
		*p = *a;
		p++;
		a++;
	}

	while (j && *j)
	{
		*p = *j;
		p++;
		j++;
	}

	while (b && *b)
	{
		*p = *b;
		p++;
		b++;
	}

	*p = '\0';

	return (s);
}

/**
 * _strtok_r - returns pointers to string as tokens based on delimiters
 *		a new token is given on subsquent calls, NULL if none found
 *
 * @s: string to tokenize
 * @delim: characters to split the string by
 * @start: keep track of last position in string
 *
 * Return: pointer to string tokens or NULL if none
 */
char *_strtok_r(char *s, char *delim, char **start)
{
	char *end;
	int len = 0;
	char chrToStr[] = {'\0', '\0'};

	if (s == NULL)
		s = *start;

	*chrToStr = *s;
	/*Skip all the delimeters*/
	while (*s && _strcontains(delim, chrToStr) != -1)
		*chrToStr = *++s;

	if (*s == '\0')
	{
		*start = s;
		return (NULL);
	}

	end = s;

	*chrToStr = *end;
	/*iterate through the token*/
	while (*end && _strcontains(delim, chrToStr) == -1)
		*chrToStr = *++end;

	if (*end == '\0')
	{
		*start = end;
		return (s);
	}

	*end = '\0';
	*start = end + 1;
	return (s);
}
