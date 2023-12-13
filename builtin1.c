#include "shell.h"

/**
 * print_history - Displays the command history with line numbers starting at 0.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int print_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias identified by a string.
 * @info: Parameter structure.
 * @str: The string representing the alias.
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign, temp_char;
	int result;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);

	temp_char = *equal_sign;
	*equal_sign = '\0';

	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*equal_sign = temp_char;
	return (result);
}

/**
 * add_alias - Adds an alias identified by a string.
 * @info: Parameter structure.
 * @str: The string representing the alias.
 * Return: Always 0 on success, 1 on error.
 */
int add_alias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - Displays an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int display_alias(list_t *node)
{
	char *equal_sign = NULL, *alias_start = NULL;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias_start = node->str; alias_start <= equal_sign; alias_start++)
			_putchar(*alias_start);

		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Manages aliases by displaying, adding, or removing them.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *current_alias = NULL;

	if (info->argc == 1)
	{
		current_alias = info->alias;
		while (current_alias)
		{
			display_alias(current_alias);
			current_alias = current_alias->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			add_alias(info, info->argv[i]);
		else
			display_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
