#include "main.h"

/**
 * _strdup - copies a string to new heap location
 *
 * @s: string to copy
 *
 * Return: pointer to new string copy
 */
char *_strdup(char *s)
{
	int len, i;
	char *s_cpy;

	if (s == NULL)
		return (NULL);

	len = _strlen(s);
	s_cpy = malloc(len + 1);

	for (i = 0; i <= len; i++)
		*(s_cpy + i) = *(s + i);

	return (s_cpy);
}

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return:	< 0 if s1 < s2
 *		> 0 if s1 > s2
 *		0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int delta;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	for (delta = *s1 - *s2; *s1 && *s2 && delta == 0; s1++, s2++)
		delta = *s1 - *s2;

	return (delta);
}

/**
 * _strlen - get the string length
 *
 * @s: string to calculate length of
 *
 * Return: integer
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	for (; *s; s++)
		len++;

	return (len);
}

/**
 * _strcontains - check whether a string contains a substring
 *
 * @s: string to check
 * @sub: substring to look for
 *
 * Return:	index of first occurrence of substring is found
 *		-1 if not found
 */
int _strcontains(char *s, char *sub)
{
	int pos = 0, i;
	int sublen = _strlen(sub);

	if (s == NULL)
		return (-1);

	while (*s)
	{
		i  = 0;
		while (i < sublen)
		{
			if (*(s + i) != *(sub + i))
			{
				s++;
				pos++;
				break;
			}
			i++;
		}
		if (i == sublen)
			return (pos);
	}

	return (-1);
}
