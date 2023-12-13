#include "shell.h"

/**
 * initialize_shell_info - initializes custom_info_t structure
 * @custom_info: structure address
 */
void initialize_shell_info(custom_info_t *custom_info)
{
	custom_info->custom_arg = NULL;
	custom_info->custom_argv = NULL;
	custom_info->custom_path = NULL;
	custom_info->custom_argc = 0;
}

/**
 * configure_shell_info - configures custom_info_t structure
 * @custom_info: structure address
 * @custom_av: custom argument vector
 */
void configure_shell_info(custom_info_t *custom_info, char **custom_av)
{
	int i = 0;

	custom_info->custom_fname = custom_av[0];
	if (custom_info->custom_arg)
	{
		custom_info->custom_argv = custom_strtow(custom_info->custom_arg, " \t");
		if (!custom_info->custom_argv)
		{
			custom_info->custom_argv = malloc(sizeof(char *) * 2);
			if (custom_info->custom_argv)
			{
				custom_info->custom_argv[0] = custom_strdup(custom_info->custom_arg);
				custom_info->custom_argv[1] = NULL;
			}
		}
		for (i = 0; custom_info->custom_argv && custom_info->custom_argv[i]; i++)
			;
		custom_info->custom_argc = i;

		replace_custom_alias(custom_info);
		replace_custom_vars(custom_info);
	}
}

/**
 * release_shell_info - releases custom_info_t structure fields
 * @custom_info: structure address
 * @free_all: true if freeing all fields
 */
void release_shell_info(custom_info_t *custom_info, int free_all)
{
	ffree(custom_info->custom_argv);
	custom_info->custom_argv = NULL;
	custom_info->custom_path = NULL;
	if (free_all)
	{
		if (!custom_info->custom_cmd_buf)
			free(custom_info->custom_arg);
		if (custom_info->custom_env)
			free_custom_list(&(custom_info->custom_env));
		if (custom_info->custom_history)
			free_custom_list(&(custom_info->custom_history));
		if (custom_info->custom_alias)
			free_custom_list(&(custom_info->custom_alias));
		ffree(custom_info->custom_environ);
		custom_info->custom_environ = NULL;
		bfree((void **)custom_info->custom_cmd_buf);
		if (custom_info->custom_readfd > 2)
			close(custom_info->custom_readfd);
		_putchar(BUF_FLUSH);
	}
}
