#include "minishell.h"

t_command	*add_cmd(t_command *head, char *cmd, enum e_next_code next_flag)
{
	t_command	*buf;
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (node == 0)
		return (0);
	node->cmd = cmd;
	if (!node->cmd)
		return (0);
	node->next_flag = next_flag;
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

t_command	*get_n_cmd(t_command *head, int n)
{
	int			i;
	t_command	*buf;

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

int	len_cmd(t_command *head)
{
	int			i;
	t_command	*buf;

	i = 0;
	buf = head;
	while (buf)
	{
		i += 1;
		buf = buf->next;
	}
	return (i);
}
