#include "shell.h"

/**
 * check_executable - checks if a file is an executable command
 * @shell_info: the shell information struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_executable(shell_info_t *shell_info, char *file_path)
{
	struct stat file_stats;

	(void)shell_info;
	if (!file_path || stat(file_path, &file_stats))
		return (0);

	if (file_stats.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_characters - duplicates characters
 * @path_str: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to a new buffer
 */
char *copy_characters(char *path_str, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
		if (path_str[i] != ':')
			buffer[k++] = path_str[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_executable_path - finds the command in the PATH string
 * @shell_info: the shell information struct
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_executable_path(shell_info_t *shell_info, char *path_str, char *command)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (check_executable(shell_info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = copy_characters(path_str, current_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (check_executable(shell_info, path))
				return (path);
			if (!path_str[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
