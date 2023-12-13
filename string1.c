#include "shell.h"

/**
 * _copyString - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Returns: pointer to destination
 */
char *_copyString(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = 0;
	return (destination);
}

/**
 * _duplicateString - duplicates a string
 * @str: the string to duplicate
 *
 * Returns: pointer to the duplicated string
 */
char *_duplicateString(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * _printString - prints an input string
 * @str: the string to be printed
 *
 * Returns: Nothing
 */
void _printString(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_outputCharacter(str[index]);
		index++;
	}
}

/**
 * _outputCharacter - writes the character c to stdout
 * @character: The character to print
 *
 * Returns: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _outputCharacter(char character)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (character != BUF_FLUSH)
		buffer[i++] = character;
	return (1);
}
