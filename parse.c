#include "main.h"
/**
 * filterComment - find an indicator in the command and end the string there
 *
 * @s: command to check for comment indicator
 * @indicator: indicator that signifies a comment e.g. '#'
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
