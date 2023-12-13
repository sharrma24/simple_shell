#include "shell.h"

/**
 * print_error_string - Displays an error string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void print_error_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		put_error_char(str[i]);
		i++;
	}
}

/**
 * put_error_char - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_error_char(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_to_fd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_to_fd - Displays an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_to_fd(*str++, fd);
	}
	return (i);
}
