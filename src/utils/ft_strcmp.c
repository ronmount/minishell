#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	count;

	count = 0;
	while ((s1[count] || s2[count]))
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}
