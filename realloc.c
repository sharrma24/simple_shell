#include "shell.h"

/**
 * _set_memory - fills memory with a constant byte
 * @dest: the pointer to the memory area
 * @value: the byte to fill *dest with
 * @size: the amount of bytes to be filled
 * Return: (dest) a pointer to the memory area dest
 */
char *_set_memory(char *dest, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		dest[i] = value;
	return (dest);
}

/**
 * free_strings - frees a string of strings
 * @str_array: string of strings
 */
void free_strings(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the old block.
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
