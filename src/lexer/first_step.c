#include "minishell.h"

void	first_step(t_data *data, char *str)
{
	int		single_quote;
	int		double_quote;
	int		i;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (!double_quote)
			{
				single_quote = !single_quote;
				continue ;
			}
		}
		else if (str[i] == '\"')
		{
			if (!single_quote)
			{
				double_quote = !double_quote;
				continue ;
			}
		}
		else if (str[i] == '&')
		{
			if (str[i + 1] == '&' && !single_quote && !double_quote)
			{
				// todo: split me here
				i += 1;
				continue ;
			}
			write(1, &str[i], 1);
			continue ;
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|' && !single_quote && !double_quote)
			{
				// todo: split me here
				i += 1;
				continue ;
			}
			// todo: pipe me here
			continue ;
		}
		write(1, &str[i], 1);
	}
}
