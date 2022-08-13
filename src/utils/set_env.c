#include "../../include/minishell.h"

t_list	*split_n_save_env(char **env)
{
	int		i;
	int		j;
	char	*map[2];
	t_list	*envp; // the array of env
	char	*sep; // separator/separated part

	i = -1;
	envp = 0;
	map[0] = NULL;
	map[1] = NULL;
	while (env[++i])
	{
		sep = ft_strchr(env[i], '='); //strchr returns the separator and the env variable part after separator (the pointer to that part)
		if (sep)
		{
			j = ft_strlen(env[i]) - ft_strlen(sep); // ex. "USER=tasha" -> "USER=tasha"(10) - "=tasha"(6) = 4 symbols
			map[0] = ft_calloc(j + 1, sizeof(char)); //calloc allocates memory for "USER"(key) and fills it with '\0'
			ft_strlcpy(map[0], env[i], j + 1); // strlcpy copies env[i] to head->key with the size of key("USER") + 1 (1 for '\0')
			map[1] = ft_strdup(env[i] + j + 1); // strdup allocates memory and dublicates the value("tasha") + 1 (1 for '\0'), 
												     // where "env[i] + j + 1" is a pointer to the beginning of the str needed 2 be dublicated
		}
		else //if the env variable doesnt't contain '='
		{
			map[0] = ft_strdup(env[i]);
			map[1] = ft_strdup("");
		}
		envp = add(envp, (void *)map[0], (void *)map[1]);
	}
	return (envp);
}

void	print_env(t_list *envp)
{
	int		i;
	t_list	*elem;
	t_list	*tmp;

	tmp = envp;
	i = -1;
	while (tmp)
	{
		++i;
		elem = get_elem(envp, i);
		printf("%s=%s\n", (char *)elem->key, (char *)elem->value);
		tmp = tmp->next;
	}
}
