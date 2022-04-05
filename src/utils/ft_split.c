#include <minishell.h>

int	is_sep(char c)
{
	if (c == '\n' || c == '\0')
		return (1);
	return (0);
}

int	words_counter(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		if (!is_sep(str[i]) && is_sep(str[i + 1]))
			words++;
		i++;
	}
	return (words);
}

char	**gen_array(char *str, int words)
{
	char	**array;
	int		i;
	int		k;
	int		w;

	i = 0;
	k = 0;
	w = 0;
	array = malloc(sizeof(char *) * (words + 1));
	array[words] = 0;
	while (str[i] != '\0')
	{
		if (!is_sep(str[i]))
			k++;
		if (!is_sep(str[i]) && is_sep(str[i + 1]))
		{
			array[w] = malloc(sizeof(char) * (k + 1));
			k = 0;
			w++;
		}
		i++;
	}
	return (array);
}

void	fill_array(char **array, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (!is_sep(str[i]))
		{
			array[j][k] = str[i];
			k++;
		}
		if (!is_sep(str[i]) && is_sep(str[i + 1]))
		{
			array[j][k] = '\0';
			j++;
			k = 0;
		}
		i++;
	}
}

char	**ft_split(char *str)
{
	int		words;
	char	**array;

	words = words_counter(str);
	array = gen_array(str, words);
	fill_array(array, str);
	return (array);
}
