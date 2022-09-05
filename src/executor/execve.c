#include "minishell.h"

int	ft_execve(char **argv, char **envp, t_data *data)
{
	char **p = list_to_envp(data->env);
	int result = execve(argv[0], argv, p);

	int i = -1;
	while (p[++i])
		free(p[i]);
	free(p);

	return (result);
}