#include "main.h"

#define SIZE 1

/**
 * getInput - get string input from the user
 *
 * @mode: 2 - Free memory
 *
 * Return: pointer to string input
 */
char *getInput(int mode)
{
	char buf[SIZE];
	int len = 0, capacity = SIZE;
	static int firstRun = 1;
	static char *line;
	ssize_t bytes;
	if (mode == FREE && !firstRun)
	{
		free(line);
		return (NULL);
	}
	if (firstRun)
	{
		firstRun = 0;
		line = malloc(SIZE);
	}
	while ((bytes = read(STDIN_FILENO, buf, SIZE)) > 0)
	{
		for (int i = 0; i < bytes; i++)
		{
			if (buf[i] == '\n')
			{
				line = realloc(line, len + 1);
				line[len] = '\0';
				return (line);
			}
			if (len == capacity)
			{
				capacity *= 2;
				line = realloc(line, capacity);
			}
			line[len++] = buf[i];
		}
	}
	if(bytes == 0)		/* read EOF*/
	{
		free(line);
		_environ(NULL, FREE);
		exit(0);
	}
	if (bytes < 0) {
		perror("read error");
		exit(1);
	}
	line = realloc(line, len + 1);
	line[len] = '\0';
	return (line);
}
