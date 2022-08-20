#include "minishell.h"

t_pipe_group	*add_pipe_group(t_pipe_group *head, char *group, int next_flag)
{
	t_pipe_group	*buf;
	t_pipe_group	*node;

	node = malloc(sizeof(t_pipe_group));
	if (node == 0)
		return (0);
	node->cmds = 0;
	node->next = 0;
	node->group = group;
	node->next_flag = next_flag;
	if (!node->group)
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

t_pipe_group	*get_n_pipe_group(t_pipe_group *head, int n)
{
	int					i;
	t_pipe_group		*buf;

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

int	len_pipe_group(t_pipe_group *head)
{
	int				i;
	t_pipe_group	*buf;

	i = 0;
	buf = head;
	while (buf)
	{
		i += 1;
		buf = buf->next;
	}
	return (i);
}
