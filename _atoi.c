#include "shell.h"

/**
 * check_interactive_mode - Determine if the shell is running in interactive mode.
 * @info: Pointer to information about the shell.
 *
 * Returns 1 if the shell is in interactive mode, 0 otherwise.
 */
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to be checked.
 * @delim: The set of delimiter characters.
 *
 * Returns 1 if the character is a delimiter, 0 otherwise.
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
 *
 * Returns 1 if the character is alphabetic, 0 otherwise.
 */
int is_alphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_integer - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Returns 0 if the string contains no numbers, otherwise returns the converted number.
 */
int string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2
	}

	return (sign * result);
}
