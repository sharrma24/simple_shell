#include "shell.h"

/**
 * lst_len - determines length of linked list
 * @lst: pointer to first node
 *
 * Return: size of list
 */
size_t lst_len(const list_t *lst)
{
	size_t count = 0;

	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/**
 * lst_to_strings - returns an array of strings of the lst->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **lst_to_strings(list_t *head)
{
	list_t *current = head;
	size_t count = lst_len(head);
	char **str_arr;
	char *str;

	if (!head || !count)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (count + 1));
	if (!str_arr)
		return (NULL);
	for (count = 0; current; current = current->next, count++)
	{
		str = malloc(_strlen(current->str) + 1);
		if (!str)
		{
			while (count-- > 0)
				free(str_arr[count]);
			free(str_arr);
			return (NULL);
		}

		str = _strcpy(str, current->str);
		str_arr[count] = str;
	}
	str_arr[count] = NULL;
	return (str_arr);
}

/**
 * print_lst - prints all elements of a list_t linked list
 * @lst: pointer to first node
 *
 * Return: size of list
 */
size_t print_lst(const list_t *lst)
{
	size_t count = 0;

	while (lst)
	{
		_puts(convert_number(lst->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(lst->str ? lst->str : "(nil)");
		_puts("\n");
		lst = lst->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with_prefix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *node_starts_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
