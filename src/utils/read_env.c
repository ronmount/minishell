#include "minishell.h"

t_list	*read_env(char **env)
{
	int		i;
	char	**tmp;
	t_list	*head;
	char	*str;

	i = -1;
	head = 0;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		head = add(head, (void *)tmp[0], (void *)tmp[1]);
	}
	return (head);
}

void	print_env(t_list *head)
{
	int		i;
	t_list	*node;
	t_list	*buf;

	buf = head;
	i = -1;
	while (buf->next)
	{
		++i;
		node = get_n(head, i);
		printf("%s – %s\n", (char *)node->k, (char *)node->v);
		buf = buf->next;
	}
}
