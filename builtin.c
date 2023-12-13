#include "shell.h"

/**
 * custom_exit - Exits the shell with a given exit status.
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */
int custom_exit(info_t *info)
{
    int exit_code;

    if (info->arguments[1]) /* Check for exit argument */
    {
        exit_code = custom_atoi(info->arguments[1]);
        if (exit_code == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _error_puts(info->arguments[1]);
            _error_putchar('\n');
            return (1);
        }
        info->error_number = exit_code;
        return (-2);
    }
    info->error_number = -1;
    return (-2);
}

/**
 * custom_change_directory - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int custom_change_directory(info_t *info)
{
    char *current_directory, *new_directory, buffer[1024];
    int chdir_result;

    current_directory = getcwd(buffer, 1024);
    if (!current_directory)
        _error_puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->arguments[1])
    {
        new_directory = custom_get_environment_variable(info, "HOME=");
        if (!new_directory)
            chdir_result = chdir((new_directory = custom_get_environment_variable(info, "PWD=")) ? new_directory : "/");
        else
            chdir_result = chdir(new_directory);
    }
    else if (custom_strcmp(info->arguments[1], "-") == 0)
    {
        if (!custom_get_environment_variable(info, "OLDPWD="))
        {
            _error_puts(current_directory);
            _error_putchar('\n');
            return (1);
        }
        _error_puts(custom_get_environment_variable(info, "OLDPWD=")), _error_putchar('\n');
        chdir_result = chdir((new_directory = custom_get_environment_variable(info, "OLDPWD=")) ? new_directory : "/");
    }
    else
        chdir_result = chdir(info->arguments[1]);

    if (chdir_result == -1)
    {
        print_error(info, "can't cd to ");
        _error_puts(info->arguments[1]), _error_putchar('\n');
    }
    else
    {
        custom_set_environment_variable(info, "OLDPWD", custom_get_environment_variable(info, "PWD="));
        custom_set_environment_variable(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * custom_help - Displays help information. (Not yet implemented)
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int custom_help(info_t *info)
{
    char **arg_array;

    arg_array = info->arguments;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* Temporary unused variable workaround */
    return (0);
}
