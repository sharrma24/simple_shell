#include "shell.h"

/**
 * custom_str_copy - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @max_chars: the maximum number of characters to be copied
 * Return: the copied string
 */
char *custom_str_copy(char *destination, char *source, int max_chars)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < max_chars - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < max_chars)
	{
		j = i;
		while (j < max_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return result;
}

/**
 * custom_str_concat - concatenates two strings
 * @first: the first string
 * @second: the second string
 * @max_bytes: the maximum number of bytes to be used
 * Return: the concatenated string
 */
char *custom_str_concat(char *first, char *second, int max_bytes)
{
	int i, j;
	char *result = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (second[j] != '\0' && j < max_bytes)
	{
		first[i] = second[j];
		i++;
		j++;
	}
	if (j < max_bytes)
		first[i] = '\0';
	return result;
}

/**
 * custom_str_find - locates a character in a string
 * @str: the string to be parsed
 * @character: the character to look for
 * Return: a pointer to the memory area of the string
 */
char *custom_str_find(char *str, char character)
{
	do {
		if (*str == character)
			return str;
	} while (*str++ != '\0');

	return NULL;
}
