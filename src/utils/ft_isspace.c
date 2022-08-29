#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\f' || c == '\v'
		|| c == '\t' || c == '\r')
		return (1);
	else
		return (0);
}
