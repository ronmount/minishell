#include "minishell.h"

t_exit_group	*add_exit_group(t_exit_group *head, char *group, int next_flag)
{
	t_exit_group	*buf;
	t_exit_group	*node;

	node = malloc(sizeof(t_exit_group));
	if (node == 0)
		return (0);
	node->pipe_groups = 0;
	node->next = 0;
	node->exit_group = group;
	node->next_flag = next_flag;
	if (!node->exit_group)
		return (0);
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

t_exit_group	*get_n_exit_group(t_exit_group *head, int n)
{
	int					i;
	t_exit_group		*buf;

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

int	len_exit_group(t_exit_group *head)
{
	int				i;
	t_exit_group	*buf;

	i = 0;
	buf = head;
	while (buf)
	{
		i += 1;
		buf = buf->next;
	}
	return (i);
}
