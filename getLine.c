#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t read_bytes = 0;
	size_t current_length = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		read_bytes = getline(buffer, &current_length, stdin);
#else
		read_bytes = custom_getline(info, buffer, &current_length);
#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0'; /* remove trailing newline */
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
		}
	}
	return (read_bytes);
}

/**
 * get_user_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_user_input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t position_i, position_j, buffer_length;
	ssize_t read_bytes = 0;
	char **buffer_ptr = &(info->arg), *pointer;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(info, &buffer, &buffer_length);
	if (read_bytes == -1) /* EOF */
		return (-1);
	if (buffer_length) /* we have commands left in the chain buffer */
	{
		position_j = position_i; /* init new iterator to current buffer position */
		pointer = buffer + position_i; /* get pointer for return */

		check_chain(info, buffer, &position_j, position_i, buffer_length);
		while (position_j < buffer_length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &position_j))
				break;
			position_j++;
		}

		position_i = position_j + 1; /* increment past nulled ';'' */
		if (position_i >= buffer_length) /* reached end of buffer? */
		{
			position_i = buffer_length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORMAL;
		}

		*buffer_ptr = pointer; /* pass back pointer to current command position */
		return (_strlen(pointer)); /* return length of current command */
	}

	*buffer_ptr = buffer; /* else not a chain, pass back buffer from custom_getline() */
	return (read_bytes); /* return length of buffer from custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @position_i: size
 *
 * Return: read_bytes
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *position_i)
{
	ssize_t read_bytes = 0;

	if (*position_i)
		return (0);
	read_bytes = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (read_bytes >= 0)
		*position_i = read_bytes;
	return (read_bytes);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: buffer_size
 */
int custom_getline(info_t *info, char **pointer, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t position_i, buffer_length;
	size_t k;
	ssize_t read_bytes = 0, buffer_size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pointer;
	if (p && length)
		buffer_size = *length;
	if (position_i == buffer_length)
		position_i = buffer_length = 0;

	read_bytes = read_buffer(info, buffer, &buffer_length);
	if (read_bytes == -1 || (read_bytes == 0 && buffer_length == 0))
		return (-1);

	c = _strchr(buffer + position_i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_p = _realloc(p, buffer_size, buffer_size ? buffer_size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (buffer_size)
		_strncat(new_p, buffer + position_i, k - position_i);
	else
		_strncpy(new_p, buffer + position_i, k - position_i + 1);

	buffer_size += k - position_i;
	position_i = k;
	p = new_p;

	if (length)
		*length = buffer_size;
	*pointer = p;
	return (buffer_size);
}

/**
 * interruptHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void interruptHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
