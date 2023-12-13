#include "custom_shell.h"

/**
 * print_current_environment - Displays the current environment variables.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int print_current_environment(info_t *info)
{
	print_list_str(info->environment);
	return (0);
}

/**
 * get_environment_variable - Retrieves the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *get_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->environment;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initializes a new environment variable
 *                            or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_set_environment_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unset_environment_variable(info, info->argv[i]);

	return (0);
}

/**
 * initialize_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int initialize_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->environment = node;
	return (0);
}
