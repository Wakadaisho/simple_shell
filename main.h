#ifndef _MAIN_H_
#define _MAIN_H_
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * getInput - get string input from the user
 *
 * Return: pointer to string input
 */
char *getInput(void);

/**
 * tokenize - split a string into an array of strings
 *		based on certain DELIMS (delimiters)
 * @s: string to split
 * @delims: string characters to tokenize by
 *		defaults to ' ' and '\t' if NULL
 *
 * Return: array of strings, NULL if failed or no s is NULL
 */
char **tokenize(char *s, char *delims);

/**
 * executeCommand - run a command in the shell
 *
 * @args: pointer to a vector of C strings,
 *		ending with a NULL pointer
 *
 * Return: execve return value
 */
int executeCommand(char **args);

/**
 * repl - describe a transaction of:
 *		1. Taking input from the user
 *		2. Executing said input
 *		3. Printing any output
 *
 * Return: void
 */
void repl(void);

/**
 * _getenv - get the value of an environment variable
 *
 * @name: environment variable to search for
 *
 * Return:	pointer to environment variable string
 *		NULL if not found
 */
char *_getenv(char *name);

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return:	< 0 if s1 < s2
 *		> 0 if s1 > s2
 *		0 otherwise
 */
int _strcmp(char *s1, char *s2);

/**
 * _strlen - get the string length
 *
 * @s: string to calculate length of
 *
 * Return: integer
 */
int _strlen(char *s);

/**
 * _strdup - copies a string to new heap location
 *
 * @s: string to copy
 *
 * Return: pointer to new string copy
 */
char *_strdup(char *s);

/**
 * _strjoin - joins two strings, with an optional joining string
 *		returning a new pointer to string
 * @a: first string
 * @b: second string
 * @j: optional jointer string
 *
 * Return: pointer to new string
 */
char *_strjoin(char *a, char *b, char *j);

/**
 * _environ - get environment variables from anywhere, statically
 *
 * @env:	environment variables to store, NULL to reuse stored
 * @mode:	0 - default, ovewrites environ to env if exists
 *		1 - free environ then quit (ignores env)
 *
 * Return:	pointer to environment variable strings
 *		NULL if environment not previously given
 */
char **_environ(char **env, int mode);

/**
 * _strcontains - check whether a string contains a substring
 *
 * @s: string to check
 * @sub: substring to look for
 *
 * Return:	index in string if substring is found
 *		-1 if not found
 */
int _strcontains(char *s, char *sub);

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
char *_strtok_r(char *s, char *delim, char **start);

/**
 * _realloc - reallocates memory for an array of pointers
 *
 * @arr: array of pointers to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: void
 */
void **_realloc(void **arr, int old_size, int new_size);

/**
 * getCmdPath - check whether a command exist in another path
 *		and return that path
 *
 * @cmd: command to check in the PATH variable
 *
 * Return:	new path if exists
 *		NULL if path does not exist
 */
char *getCmdPath(char *cmd);

/**
 * filterComment - find an indicator in the command and end the string there
 *
 * @s: command to check for comment indicator
 * @indicator: indicator that signifies a comment e.g. '#'
 *
 * Return: void
 */
void filterComment(char *s, char *indicator);

#endif /* _MAIN_H_ */
