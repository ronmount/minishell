#include "minishell.h"

int	count_substrings(char *str, char sep)
{
	int	i;
	int	c;
	int	in_sep;
	int	single_quote;
	int	double_quote;

	i = -1;
	c = 0;
	in_sep = 0;
	single_quote = 0;
	double_quote = 0;
	// s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '\"' && !single_quote)
			double_quote = !double_quote;

		i += 1;
	}
	return (c);
}

char	**cmd_split(char *cmd)
{
	char	**a;
	printf("%d\n", count_substrings(cmd, ' '));
	return (a);
}