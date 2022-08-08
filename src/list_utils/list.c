#include "minishell.h"

t_list	*add(t_list *head, void *k, void *v)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == 0)
		return (0);
	node->k = k;
	node->v = v;
	if (head)
		head->next = node;
	else
		return (node);
	return (head);
}

t_list	*del(t_list *head, t_list *del_node)
{
	t_list	*buf;

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
				// TODO: free k, v etc
				free(head);
				return (buf);
			}
			buf->next = del_node->next;
			// TODO: free k, v etc
			free(del_node);
			return (head);
		}
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
		if (!ft_strcmp((char *)buf->k, (char *)k))
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
	while (buf && ++i)
	{
		if (i == n)
			return (buf);
		buf = buf->next;
	}
	return (0);
}
