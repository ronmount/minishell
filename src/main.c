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
	int				lp;
	t_exit_group	*g;

	i = -1;
	split_exit_groups(data, str);
	lg = len_exit_group(data->exit_groups);
	while (++i < lg)
	{
		j = -1;
		g = get_n_exit_group(data->exit_groups, i);
		split_pipe_groups(data, g);
		lp = len_pipe_group(g->pipe_groups);
		while (++j < lp)
			split_cmd(data, get_n_pipe_group(g->pipe_groups, j));
	}
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*str;

	data = init(env);
//	cmd_split("lol hi lol \" kek \" \' \' \" \' \' \"");

	char **test = list_to_envp(data->env);
	for (int i = len(data->env)-1; i >= 0; i--)
	{
		printf("%s\n", test[i]);
	}
	return 0;
	while (1) {
		str = readline("minishell: ");
		if (!str)
			continue ;
		parse_line(data, str);
		int i = -1;
		int egl = len_exit_group(data->exit_groups);
		while (++i < egl) {
			t_exit_group *eg = get_n_exit_group(data->exit_groups, i);
			printf("eg: [%s], next: %d\n", eg->exit_group, eg->next_flag);
			int pgl = len_pipe_group(eg->pipe_groups);
			int j = -1;
			while (++j < pgl) {
				t_pipe_group  *pg = get_n_pipe_group(eg->pipe_groups, j);
				printf("\tpg: [%s]\n", pg->group);
				int k = -1;
				int cl = len_cmd(pg->cmds);
				while (++k < cl) {
					t_command *c = get_n_cmd(pg->cmds, k);
					printf("\t\tc: [%s], next: %d\n", c->cmd, c->next_flag);
				}
			}
		}
		clean_exit_groups(data);
	}
	return (0);
}
