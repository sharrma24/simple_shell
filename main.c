#include "shell.h"

/**
 * free_and_null - deallocates memory for a pointer and sets it to NULL
 * @ptr: address of the pointer to be freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

