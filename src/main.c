#include "minishell.h"

t_data	*init(char **env)
{
	t_data 	*data;
	char	**builtin;
	int 	i;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	i = -1;
	builtin = ft_split(BUILTIN, ':');
	data->env = NULL;
	data->builtin = NULL;
	data->env = read_env(env);
	while (builtin[++i])
		data->builtin = add(data->builtin, (void *) builtin[i], (void *) builtin[i]);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	char	*buf;
	t_list *list;
	t_data *data;
	data = init(env);
	printf("%d %d", execve("/bin/pwd", argv, env), errno);
	return (0);
}
