#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**tmp;
	t_list	*head;
	t_list	*node;

	i = -1;
	head = 0;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		head = add(head, (void *)tmp[0], (void *)tmp[1]);
	}
	i = -1;
	while (tmp[++i])
	{
		node = get_n(head, i);
		printf("%s – %s\n", (char *)node->k, (char *)node->v);
	}
	return (0);
}
