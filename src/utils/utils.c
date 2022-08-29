#include "minishell.h"

char	*clean_spaces(char *str)
{
	int		i;
	int		j;
	int		end;
	char	*res;

	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	end = (int)ft_strlen(str) -1;
	j = -1;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isspace(str[end]))
		end--;
	while (str[i] && i <= end)
		res[++j] = str[i++];
	free(str);
	return (res);
}
