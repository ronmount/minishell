#include "minishell.h"

t_data	*init(char **env)
{
	t_data	*data;
	char	**splitted_builtins;
	int		i;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	i = -1;
	splitted_builtins = ft_split(BUILTIN, ':');
	data->env = NULL;
	data->builtin = NULL;
	data->env = read_env(env);
	data->exit_groups = 0;
	while (splitted_builtins[++i])
		data->builtin = add(data->builtin,
				(void *) splitted_builtins[i], (void *) splitted_builtins[i]);
	return (data);
}

t_data	*parse_line(t_data *data, char *str)
{
	int				i;
	int				j;
	int				lg;
	int				lc;
	t_exit_group	*g;
	t_pipe_group	*c;

	i = -1;
	split_exit_groups(data, str);
	lg = len_exit_group(data->exit_groups);
	while (++i < lg)
	{
		j = -1;
		g = get_n_exit_group(data->exit_groups, i);
		split_pipe_groups(data, g);
		lc = len_pipe_group(g->pipe_groups);
		while (++j < lc)
			c = get_n_pipe_group(g->pipe_groups, j);
	}
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*str;

	data = init(env);
	str = readline("minishell: ");
	parse_line(data, str);
	return (0);
}
