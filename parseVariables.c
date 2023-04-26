#include "main.h"

/**
 * parseVariables - go through tokens and replace environment variables
 *
 * @tokens: list of strings to replace if possible
 *
 * Return: void
 */
void parseVariables(char **tokens)
{
	int i = 0;
	char *parsed = NULL;

	for (i = 0; tokens[i]; i++)
	{
		if (tokens[i][0] != '$')
			continue;
		if (_strcmp(tokens[i], "$$") == 0)
		{
			parsed = _itoa(getpid());
			free(tokens[i]);
			tokens[i] = parsed;
			parsed = NULL;
			continue;
		}
		if (_strcmp(tokens[i], "$?") == 0)
		{
			parsed = _itoa(accessErrorCode(0, READ));
			free(tokens[i]);
			tokens[i] = parsed;
			parsed = NULL;
			continue;
		}
		parsed = _getenv(tokens[i]);
		if (parsed)
		{
			free(tokens[i]);
			tokens[i] = parsed;
			parsed = NULL;
		}
	}
}
