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
	while (splitted_builtins[++i])
		data->builtin = add(data->builtin,
				(void *) splitted_builtins[i], (void *) splitted_builtins[i]);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*str;

	data = init(env);
	while (1)
	{
		str = readline("minishell: ");
		first_step(data, str);
		write(1, "\n", 1);
	}
	return (0);
}
