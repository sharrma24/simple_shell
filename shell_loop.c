#include "shell.h"

/**
 * hsh - main shell loop
 * @info_struct: the parameter & return info struct
 * @arg_vector: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info_struct, char **arg_vector)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_info(info_struct);
		if (interactive(info_struct))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_result = get_input(info_struct);
		if (input_result != -1)
		{
			set_info(info_struct, arg_vector);
			builtin_result = find_builtin(info_struct);
			if (builtin_result == -1)
				find_cmd(info_struct);
		}
		else if (interactive(info_struct))
			_putchar('\n');
		free_info(info_struct, 0);
	}
	write_history(info_struct);
	free_info(info_struct, 1);
	if (!interactive(info_struct) && info_struct->status)
		exit(info_struct->status);
	if (builtin_result == -2)
	{
		if (info_struct->err_num == -1)
			exit(info_struct->status);
		exit(info_struct->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - finds a builtin command
 * @info_struct: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *info_struct)
{
	int i, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info_struct->argv[0], builtintbl[i].type) == 0)
		{
			info_struct->line_count++;
			built_in_result = builtintbl[i].func(info_struct);
			break;
		}
	return (built_in_result);
}

/**
 * find_cmd - finds a command in PATH
 * @info_struct: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info_struct)
{
	char *path = NULL;
	int i, k;

	info_struct->path = info_struct->argv[0];
	if (info_struct->linecount_flag == 1)
	{
		info_struct->line_count++;
		info_struct->linecount_flag = 0;
	}
	for (i = 0, k = 0; info_struct->arg[i]; i++)
		if (!is_delim(info_struct->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info_struct, _getenv(info_struct, "PATH="), info_struct->argv[0]);
	if (path)
	{
		info_struct->path = path;
		fork_cmd(info_struct);
	}
	else
	{
		if ((interactive(info_struct) || _getenv(info_struct, "PATH=")
					|| info_struct->argv[0][0] == '/') && is_cmd(info_struct, info_struct->argv[0]))
			fork_cmd(info_struct);
		else if (*(info_struct->arg) != '\n')
		{
			info_struct->status = 127;
			print_error(info_struct, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info_struct: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info_struct)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info_struct->path, info_struct->argv, get_environ(info_struct)) == -1)
		{
			free_info(info_struct, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info_struct->status));
		if (WIFEXITED(info_struct->status))
		{
			info_struct->status = WEXITSTATUS(info_struct->status);
			if (info_struct->status == 126)
				print_error(info_struct, "Permission denied\n");
		}
	}
}
