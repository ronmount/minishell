#include "minishell.h"

t_list	*read_env(char **env)
{
	int		i;
	char	*tmp[2];
	t_list	*head;
	char	*str;
	int	j;

	i = -1;
	head = 0;
	tmp[0] = NULL;
	tmp[1] = NULL;
	while (env[++i])
	{
		str = ft_strchr(env[i], '=');
		if (str)
		{
			j = ft_strlen(env[i]) - ft_strlen(str);
			tmp[0] = ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(tmp[0], env[i], j + 1);
			tmp[1] = ft_strdup(env[i] + j + 1);
		}
		head = add(head, (void *)tmp[0], (void *)tmp[1]);
	}
	return (head);
}
