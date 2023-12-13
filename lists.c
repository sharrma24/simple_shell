#include "shell.h"

/**
 * append_node - appends a node to the start of the linked list
 * @list_head: address of pointer to the head node
 * @data: data field of the node
 * @index: node index used by history
 *
 * Return: size of the linked list
 */
list_t *append_node(list_t **list_head, const char *data, int index)
{
	list_t *new_head;

	if (!list_head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->index = index;
	if (data)
	{
		new_head->data = _strdup(data);
		if (!new_head->data)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *list_head;
	*list_head = new_head;
	return (new_head);
}

/**
 * append_node_end - appends a node to the end of the linked list
 * @list_head: address of pointer to the head node
 * @data: data field of the node
 * @index: node index used by history
 *
 * Return: size of the linked list
 */
list_t *append_node_end(list_t **list_head, const char *data, int index)
{
	list_t *new_node, *node;

	if (!list_head)
		return (NULL);

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}

/**
 * display_list_data - prints only the data element of a list_t linked list
 * @list_head: pointer to the first node
 *
 * Return: size of the linked list
 */
size_t display_list_data(const list_t *list_head)
{
	size_t size = 0;

	while (list_head)
	{
		_puts(list_head->data ? list_head->data : "(nil)");
		_puts("\n");
		list_head = list_head->next;
		size++;
	}
	return (size);
}

/**
 * remove_node_at_index - deletes a node at the given index
 * @list_head: address of pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **list_head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!index)
	{
		node = *list_head;
		*list_head = (*list_head)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *list_head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * release_list - frees all nodes of a linked list
 * @list_head_ptr: address of pointer to the head node
 *
 * Return: void
 */
void release_list(list_t **list_head_ptr)
{
	list_t *node, *next_node, *head;

	if (!list_head_ptr || !*list_head_ptr)
		return;
	head = *list_head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*list_head_ptr = NULL;
}
