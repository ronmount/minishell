#include "minishell.h"

void	split_exit_groups(t_data *data, char *str)
{
	char	*buf;
	int		single_quote;
	int		double_quote;
	int		i;
	int		j;

	i = -1;
	j = -1;
	single_quote = 0;
	double_quote = 0;
	buf = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[++i])
	{
		j += 1;
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (str[i] == '&' && str[i + 1] == '&' && !single_quote && !double_quote)
		{
			data->exit_groups = add_exit_group(data->exit_groups, ft_strdup(buf),
									NEXT_AND);
			buf = calloc(ft_strlen(str + 1), 1);
			i += 1;
			j = -1;
			continue ;
		}
		else if (str[i] == '|' && str[i + 1] == '|' && !single_quote && !double_quote)
		{
			data->exit_groups = add_exit_group(data->exit_groups, ft_strdup(buf),
									 NEXT_OR);
			buf = calloc(ft_strlen(str + 1), 1);
			i += 1;
			j = -1;
			continue ;
		}
		buf[j] = str[i];
	}
	if (ft_strlen(buf))
		data->exit_groups = add_exit_group(data->exit_groups, ft_strdup(buf),
								   NEXT_NONE);
	free(buf);
}

void	split_pipe_groups(t_data *data, t_exit_group *g)
{
	char	*buf;
	int		single_quote;
	int		double_quote;
	int		i;
	int		j;

	i = -1;
	j = -1;
	single_quote = 0;
	double_quote = 0;
	buf = ft_calloc(ft_strlen(g->exit_group) + 1, 1);
	while (g->exit_group[++i])
	{
		j += 1;
		if (g->exit_group[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (g->exit_group[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (g->exit_group[i] == '|' && !single_quote && !double_quote)
		{
			g->pipe_groups = add_pipe_group(g->pipe_groups, ft_strdup(buf),
											NEXT_NONE);
			buf = calloc(ft_strlen(g->exit_group + 1), 1);
			i += 1;
			j = -1;
			continue ;
		}
		buf[j] = g->exit_group[i];
	}
	if (ft_strlen(buf))
		g->pipe_groups = add_pipe_group(g->pipe_groups, ft_strdup(buf), NEXT_NONE);
	free(buf);
}