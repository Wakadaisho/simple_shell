#include "main.h"

#define SIZE 1024

/**
 * getInput - get string input from the user
 *
 * Return: pointer to string input
 */
char *getInput(void)
{
	char buf[SIZE] = {'\0'}, *tmp = NULL, *line = NULL;
	int bytes, total = 0;

	for (; (bytes = read(STDIN_FILENO, buf, SIZE)) > 0; total += bytes)
	{
		tmp = _strjoin(line, buf, NULL);
		if (line)
			free(line);
		line = tmp;
		if (bytes == 1 && _strcontains(line, "\n") == 0)	   /*Enter key*/
		{
			free(line);
			return (NULL);
		}
		if (_strcontains(line, "\n"))
			break;
	}
	if (total == 0)		/* read EOF*/
	{
		write(STDOUT_FILENO, "\n", 1);
		cleanMemory();
		exit(0);
	}
	if (bytes < 0)
		exit(1);
	return (line);
}


/**
 * _accesscmds - return commands and logical operators tokenized
 *
 * @args:	two lists of commands and logical operators
 * @mode:	0 - returns cmds (ignores args)
 *		1 - sets cmds, then returns it
 *		2 - free cmds then quit (ignores env)
 *
 * Return: pointer to lists of command and logical operators
 */
char ***_accesscmds(char ***args, int mode)
{
	static char ***cmds;

	if (mode == READ)
		return (cmds);

	if (mode == FREE)
	{
		if (cmds == 0)
			return (NULL);
		if (cmds[0])
			_freeTokenized(cmds[0]);
		if (cmds[1])
			_freeTokenized(cmds[1]);
		free(cmds);
		cmds = NULL;
		return (NULL);
	}

	if (mode == WRITE)
	{
		_accesscmds(NULL, FREE);
		cmds = args;
		return (cmds);
	}

	return (cmds);
}

/**
 * _readfile - open a file and read in the contents to memory
 *
 * @filename: name of file to read content from
 *
 * Return: pointer to strings list
 */
char **_readfile(char *filename)
{
	int line_len = 0, lines_len = 0, line_cap = 10, lines_cap = 10, bytes, i;
	char *c = malloc(sizeof(char));
	char *line = NULL, **lines;
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		accessErrorCode(-2, WRITE);
		cleanMemory();
		exit(1);
	}
	for (lines = malloc(lines_cap * sizeof(char *)), i = 0; i < lines_cap; i++)
		lines[i] = NULL;
	while ((bytes = read(fd, c, 1)) > 0)
	{
		if (line == NULL)
			line = malloc(line_cap * sizeof(char));
		for (; line_len >= line_cap; line_cap *= 2)
			line = _realloc(line, line_len, line_cap * 2);
		for (; lines_len >= lines_cap; lines_cap *= 2)
			lines = _reallocp(lines, lines_len, lines_cap * 2);
		if (*c == '\n')
		{
			line[line_len] = '\0';
			line_len = 0;
			lines[lines_len++] = line;
			line = NULL;
			continue;
		}
		line[line_len++] = *c;
	}
	free(c);
	close(fd);
	if (bytes == -1)
	{
		for (; lines_len >= lines_cap; lines_cap *= 2)
			lines = _reallocp(lines, lines_len, lines_cap * 2);
		lines[line_len] = NULL;
	}
	return (lines);
}
