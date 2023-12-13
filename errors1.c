#include "custom_shell.h"

/**
 * custom_str_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in the string, converted number otherwise.
 *       -1 on error.
 */
int custom_str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Investigate why this affects main returning 255. */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > CUSTOM_INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_error - Prints an error message.
 * @info: The parameter and return information structure.
 * @error_string: String containing the specified error type.
 * Return: Nothing.
 */
void print_custom_error(info_t *info, char *error_string)
{
	put_custom_string(info->function_name);
	put_custom_string(": ");
	print_custom_int(info->line_count, STDERR_FILENO);
	put_custom_string(": ");
	put_custom_string(info->arguments[0]);
	put_custom_string(": ");
	put_custom_string(error_string);
}

/**
 * print_custom_int - Function prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_custom_int(int input, int fd)
{
	int (*__putchar)(char) = custom_putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		__putchar = custom_error_putchar;
	if (input < 0)
	{
		abs_value = -input;
		__putchar('-');
		count++;
	}
	else
		abs_value = input;
	current = abs_value;
	for (i = CUSTOM_INT_MAX_DIGITS; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_integer - Converter function, a clone of itoa.
 * @num: Number to convert.
 * @base: Base for conversion.
 * @flags: Argument flags.
 *
 * Return: String representation of the number.
 */
char *convert_integer(long int num, int base, int flags)
{
	static char *array;
	static char buffer[CUSTOM_CONVERT_BUFFER_SIZE];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CUSTOM_CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CUSTOM_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[CUSTOM_CONVERT_BUFFER_SIZE - 1];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
