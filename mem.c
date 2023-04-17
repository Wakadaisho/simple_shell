#include "main.h"

/**
 * _realloc - reallocates memory for an array of data
 *
 * @arr: array of data to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: void pointer;
 */
void *_realloc(void *arr, int old_size, int new_size)
{
	int i;
	char *p = (char *) arr;

	if (new_size == 0)
	{
		if (arr)
			free(arr);
		return (NULL);
	}

	if (old_size >= new_size)
		return (arr);

	char *new_arr = malloc(new_size * sizeof(char));

	for (i = 0; i < old_size; i++)
		new_arr[i] = p[i];

	free(arr);

	return ((void *)new_arr);
}

/**
 * _reallocp - reallocates memory for an array of pointers
 *
 * @arr: array of pointers to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: void pointer to pointers
 */
void **_reallocp(void **arr, int old_size, int new_size)
{
	int i;

	if (new_size == 0)
	{
		if (arr)
			free(arr);
		return (NULL);
	}

	if (old_size >= new_size)
		return (arr);

	void **new_arr = malloc(new_size * sizeof(void *));

	for (i = 0; i < old_size; i++)
		new_arr[i] = arr[i];

	free(arr);

	return (new_arr);
}
