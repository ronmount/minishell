#include "../../include/minishell.h"

//int	ft_env(t_data *data, t_command *command)
int	ft_env(t_data *data, char *command)
{
	t_list	*print;
    (void)command;

	print = data->env;
	while (print->next)
	{
		ft_putstr_fd(print->key, 1); // add fd later
		ft_putchar_fd('=', 1); // add fd later
		ft_putendl_fd(print->value, 1); // add fd later
		print = print->next;
	}
	ft_putstr_fd(print->key, 1); // add fd later
	ft_putchar_fd('=', 1); // add fd later
	ft_putendl_fd(print->value, 1); // add fd later
	return (0);
}