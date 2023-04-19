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

	for (; a && *a; p++, a++)
		*p = *a;

	for (; j && *j; p++, j++)
		*p = *j;

	for (; b && *b; p++, b++)
		*p = *b;

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

/**
 * _itoa - convert an integer to a string
 *
 * @n:integer to convert to a string
 *
 * Return:	pointer to string
 *		NULL on failure
 */
char *_itoa(int n)
{
	char *n_str;
	int negative = n < 0, power = 1, len = 1, i = 0, tmp;

	if (negative)
	{
		n *= -1;
		len += 1;
	}

	tmp = n;

	if (n == 0)
	{
		n_str = malloc(2 * sizeof(char));
		n_str[0] = '0';
		n_str[1] = '\0';
		return (n_str);
	}

	for (; n > 9; n /= 10, len++)
		power *= 10;

	n_str = malloc((len + 1) * sizeof(char));

	if (negative)
		n_str[i++] = '-';

	for (; i < len; i++, tmp %= power, power /= 10)
		n_str[i] = '0' + tmp / power;

	n_str[i] = '\0';

	return (n_str);
}

/**
 * _atoi - convert a string to an integer
 * @s: string to convert to integer
 *
 * Return: int
 */
int _atoi(char *s)
{
	int result = 0;
	int parity = 0;
	int foundDigit = 0;

	while (*s)
	{
		if (*s == '+')
		{
			parity++;
		}
		else if (*s == '-')
		{
			parity--;
		}
		else
		{
			if (*s >= '0' && *s <= '9')
			{
				foundDigit = 1;
				result = result * 10 + (*s - '0');
			}
			else
			{
				if (foundDigit)
				{
					break;
				}
			}
		}
		s++;
	}

	return (parity < 0 ? -1 * result : result);
}
