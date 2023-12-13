#include "shell.h"

/**
 * retrieve_environment - obtains a copy of the environment variables as a string array.
 * @info: Structure holding potential arguments, ensuring consistent function prototype.
 * Return: Always 0.
 */
char **retrieve_environment(info_t *info)
{
	if (!info->environment || info->env_update_required)
	{
		info->environment = list_to_strings(info->env);
		info->env_update_required = 0;
	}

	return (info->environment);
}

/**
 * _remove_env_var - Deletes an environment variable.
 * @info: Structure holding potential arguments, ensuring consistent function prototype.
 * Return: 1 on successful deletion, 0 otherwise.
 * @variable: String representing the environment variable.
 */
int _remove_env_var(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *pointer;

	if (!node || !variable)
		return (0);

	while (node)
	{
		pointer = starts_with(node->str, variable);
		if (pointer && *pointer == '=')
		{
			info->env_update_required = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_update_required);
}

/**
 * _modify_env - Initializes a new environment variable or modifies an existing one.
 * @info: Structure holding potential arguments, ensuring consistent function prototype.
 * @variable: String representing the environment variable.
 * @value: String representing the environment variable value.
 * Return: Always 0.
 */
int _modify_env(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *pointer;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		pointer = starts_with(node->str, variable);
		if (pointer && *pointer == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_update_required = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_update_required = 1;
	return (0);
}
