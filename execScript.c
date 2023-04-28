#include <sys/wait.h>
#include <errno.h>
#include "main.h"

/**
 * cmdOrAlias - determine whether a command is an alias
 *		and then tokenize appropriately
 *
 * @cmd: command to check
 *
 * Return: pointer to strings
 */

char **cmdOrAlias(char *cmd)
{
	char *alias = NULL, **tokens = NULL;

	alias = _getalias(cmd);

	if (alias)
	{
		tokens = tokenize(alias, " \t\n");
		free(alias);
	}
	else
	{
		tokens = tokenize(cmd, " \t\n");
	}

	return (tokens);
}

/**
 * execScript - execute commands in a file line by line
 *
 * @argv: arguments passed to main
 *
 * Return: void
 */
void execScript(char **argv)
{
	char **tokens = NULL, ***cmds = NULL, *tmp, *file = NULL;
	char **lines = NULL;
	int ec = 0, i = 0, j = 0, k = 0;

	lines = _readfile(argv[1]);
	for (j = 0; lines && lines[j]; j++)
	{
		filterComment(lines[j], "#");
		if (_strlen(lines[j]) == 0)
			continue;
		cmds = _accesscmds(tokenizeCommand(lines[j]), WRITE);
		for (i = 0; cmds[0][i]; i++)
		{
			tokens = cmdOrAlias(cmds[0][i]);
			for (k = 1; tokens[k]; k++)
			{
				tmp = stripCharacters(tokens[k], "\'\"");
				free(tokens[k]);
				tokens[k] = tmp;
			}
			parseVariables(tokens);
			executeCommand(tokens);
			ec = accessErrorCode(0, READ);
			printError(cmds[0][i], argv[0]);
			_freeTokenized(tokens);
			if (cmds[1] && cmds[1][i])
				if (continueChain(cmds[1][i], ec) == 0)
					break;
		}
	}
	if (lines)
		_freeTokenized(lines);
	cleanMemory();
	exit(0);
}
