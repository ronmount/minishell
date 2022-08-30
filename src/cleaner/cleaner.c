#include "minishell.h"

void	clean_commands(t_pipe_group *p)
{
	t_command	*buf;

	buf = p->cmds;
	while (buf)
	{
		free(buf->cmd);
		buf = buf->next;
	}
	free(buf);
}

void	clean_pipe_groups(t_exit_group *p)
{
	t_pipe_group	*buf;

	buf = p->pipe_groups;
	while (buf)
	{
		clean_commands(buf);
		free(buf->group);
		buf = buf->next;
	}
	free(buf);
}

void	clean_exit_groups(t_data *p)
{
	t_exit_group	*buf;

	buf = p->exit_groups;
	while (buf)
	{
		clean_pipe_groups(buf);
		free(buf->exit_group);
		buf = buf->next;
	}
	free(buf);
	p->exit_groups = 0;
}
