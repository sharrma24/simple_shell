#include "custom_shell.h"

/**
 * get_history_filepath - retrieves the file path for storing command history
 * @info: Structure containing relevant arguments.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_filepath(info_t *info)
{
    char *path, *home_dir;

    home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return (NULL);
    path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HISTORY_FILE) + 2));
    if (!path)
        return (NULL);
    path[0] = 0;
    _strcpy(path, home_dir);
    _strcat(path, "/");
    _strcat(path, HISTORY_FILE);
    return (path);
}

/**
 * save_history - creates or appends to the history file
 * @info: Structure containing relevant arguments.
 *
 * Return: 1 on success, -1 on failure
 */
int save_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_filepath(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);
    for (node = info->command_history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * load_history - reads command history from the file
 * @info: Structure containing relevant arguments.
 *
 * Return: Number of history entries on success, 0 on failure
 */
int load_history(info_t *info)
{
    int i, last = 0, line_count = 0;
    ssize_t fd, read_len, file_size = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_filepath(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);
    if (!fstat(fd, &st))
        file_size = st.st_size;
    if (file_size < 2)
        return (0);
    buf = malloc(sizeof(char) * (file_size + 1));
    if (!buf)
        return (0);
    read_len = read(fd, buf, file_size);
    buf[file_size] = 0;
    if (read_len <= 0)
        return (free(buf), 0);
    close(fd);
    for (i = 0; i < file_size; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            add_history_entry(info, buf + last, line_count++);
            last = i + 1;
        }
    if (last != i)
        add_history_entry(info, buf + last, line_count++);
    free(buf);
    info->history_count = line_count;
    while (info->history_count-- >= MAX_HISTORY_ENTRIES)
        delete_node_at_index(&(info->command_history), 0);
    renumber_history(info);
    return (info->history_count);
}

/**
 * add_history_entry - appends an entry to the command history list
 * @info: Structure containing relevant arguments.
 * @buf: Buffer containing the command.
 * @line_count: Line count, indicating the order in the history.
 *
 * Return: Always 0
 */
int add_history_entry(info_t *info, char *buf, int line_count)
{
    list_t *node = NULL;

    if (info->command_history)
        node = info->command_history;
    add_node_end(&node, buf, line_count);

    if (!info->command_history)
        info->command_history = node;
    return (0);
}

/**
 * renumber_history - renumbers the command history list after changes
 * @info: Structure containing relevant arguments.
 *
 * Return: The new history count.
 */
int renumber_history(info_t *info)
{
    list_t *node = info->command_history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->history_count = i);
}
