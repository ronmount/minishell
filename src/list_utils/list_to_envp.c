#include "minishell.h"

char	**list_to_envp(t_list *env)
{
	t_list	*tmp;
	char	**res;
	int		len_l;
	int		i;
	char	*tmp_str;

	tmp = env;
	i = 0;
	len_l = len(tmp);
	res = (char **)malloc(sizeof (char *) * (len_l + 1));
	while (tmp)
	{
		res[i] = ft_strjoin(tmp->key, "=");
		tmp_str = ft_strjoin(res[i], tmp->value);
		free(res[i]);
		res[i] = tmp_str;
		tmp = tmp->next;
		i++;
	}
	res[i] = 0;
	return (res);
}
