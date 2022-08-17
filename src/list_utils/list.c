#include "minishell.h"

t_list	*add(t_list *head, void *k, void *v)
{
	t_list	*buf;
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == 0)
		return (0);
	node->key = k;
	node->value = v;
	node->next = 0;
	if (head)
	{
		buf = head;
		while (buf->next)
			buf = buf->next;
		buf->next = node;
		return (head);
	}
	return (node);
}

t_list	*del(t_list *head, t_list *del_node)
{
	t_list	*buf;
	t_list	*prev;

	if (head == 0)
		return (0);
	buf = head;
	while (buf)
	{
		if (buf == del_node)
		{
			if (del_node == head)
			{
				buf = head->next;
				if (head->key != head->value)
					free(head->key);
				free(head->value);
				free(head);
				return (buf);
			}
			prev->next = del_node->next;
			if (del_node->key != del_node->value)
				free(del_node->key);
			free(del_node->value);
			free(del_node);
			return (head);
		}
		prev = buf;
		buf = buf->next;
	}
	return (0);
}

t_list	*find(t_list *head, void *k)
{
	t_list	*buf;

	if (head == 0)
		return (0);
	buf = head;
	while (buf)
	{
		if (!ft_strcmp((char *)buf->key, (char *)k))
			return (buf);
		buf = buf->next;
	}
	return (0);
}

t_list	*get_n(t_list *head, int n)
{
	int		i;
	t_list	*buf;

	if (!head)
		return (0);
	buf = head;
	i = -1;
	while (buf)
	{
		i++;
		if (i == n)
			return (buf);
		buf = buf->next;
	}
	return (0);
}

int	len(t_list *head)
{
	int		i;
	t_list	*buf;

	i = 0;
	buf = head;
	while (buf)
	{
		i += 1;
		buf = buf->next;
	}
	return (i);
}