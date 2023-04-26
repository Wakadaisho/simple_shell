#include "main.h"

/**
 * _realloc - reallocates memory for an array of data
 *
 * @arr: array of data to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: char pointer
 */
char *_realloc(char *arr, int old_size, int new_size)
{
	int i;
	char *new_arr, *p;

	if (arr == NULL)
		arr = malloc(1);

	p = (char *) arr;
	if (new_size == 0)
	{
		if (arr)
			free(arr);
		return (NULL);
	}

	if (old_size >= new_size)
		return (arr);

	new_arr = malloc(new_size  * sizeof(char));

	for (i = 0; i < old_size; i++)
		new_arr[i] = p[i];

	free(arr);

	return (new_arr);
}

/**
 * _reallocp - reallocates memory for an array of pointers
 *
 * @arr: array of pointers to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: char pointer to pointers
 */
char **_reallocp(char **arr, int old_size, int new_size)
{
	char **new_arr, **p;
	int i;

	p = (char **) arr;
	if (new_size == 0)
	{
		if (arr)
			free(arr);
		return (NULL);
	}

	if (old_size >= new_size)
		return (arr);

	new_arr = malloc(new_size  * sizeof(char *));

	for (i = 0; i < old_size; i++)
		new_arr[i] = p[i];

	free(arr);

	return (new_arr);
}

/**
 * _freeTokenized - free pointer to strings data
 *
 * @arr: array to be freed
 *
 * Return:	 1 - success
 *		-1 - failure
 */
int _freeTokenized(char **arr)
{
	int i = 0;

	if (arr == NULL)
		return (1);

	for (i = 0; arr[i]; i++)
		free(arr[i]);

	free(arr);

	return (1);
}

/**
 * cleanMemory - free in use memory, such as statically allocated memory
 *
 * Return: void
 */
void cleanMemory(void)
{
	char **cd_free = malloc(sizeof(char *));

	cd_free[0] = NULL;
	getInput(FREE);
	_environ(NULL, FREE);
	_aliases(NULL, FREE);
	_accesscmds(NULL, FREE);
	bi_cd(cd_free);
	free(cd_free);
	execScript(0, NULL);
}
