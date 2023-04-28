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
	int i = 0, j = 0;
	char *parsed = NULL, *sub = NULL, *rep = NULL;
	char **environ = _environ(NULL, READ), **env = NULL;

	for (i = 0; tokens[i]; i++)
	{
		for (j = 0; environ[j]; j++)
		{
			env = tokenize(environ[j], "=");
			sub = _strjoin("$", env[0], NULL);
			parsed = _strsubstitute(tokens[i], sub, env[1]);
			free(tokens[i]);
			tokens[i] = parsed;
			free(sub);
			_freeTokenized(env);
		}
		rep = _itoa(getpid());
		parsed = _strsubstitute(tokens[i], "$$", rep);
		free(tokens[i]);
		tokens[i] = parsed;
		free(rep);
		rep = _itoa(accessErrorCode(0, READ));
		parsed = _strsubstitute(tokens[i], "$?", rep);
		free(tokens[i]);
		tokens[i] = parsed;
		free(rep);
	}
}
