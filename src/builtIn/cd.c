#include "../../include/minishell.h"

void	change_old(t_data *data)
{
	t_list	*old;
	t_list	*new;
	char	*tmp;

	old = find(data->env, "OLDPWD");
	new = find(data->env, "PWD");
	if (old)
	{
		free(old->value);
		old->value = ft_strdup(new->value);
	}
	else
	{
		tmp = ft_strjoin("OLDPWD=", new->value);
        add(data->env, new->key, new->value);
		free(tmp);
	}
}

void	change_new(t_data *data, char *newpwd)
{
	t_list	*new;

	new = find(data->env, "PWD");
	free(new->value);
	new->value = ft_strdup(newpwd);
}

int	ft_cd(t_data *data, char *dir)
{
    char    *newpwd;

    newpwd = NULL;
    chdir(dir);
    change_old(data);
    newpwd = getcwd(newpwd, 1000);
	change_new(data, newpwd);
	if (newpwd)
		free(newpwd);
    return (0);
}
