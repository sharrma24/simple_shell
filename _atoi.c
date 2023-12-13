#include "shell.h"

/**
 * check_interactive_mode - Determine if the shell is running in interactive mode.
 * @info: Pointer to information about the shell.
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to be checked.
 * @delim: The set of delimiter characters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alphabetic - Check if a character is an alphabetic character.
 * @c: The character to be checked.
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int is_alphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
