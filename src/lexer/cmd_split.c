#include "minishell.h"

static int	*ft_count_size(const char *str, int cw, char sep)
{
	int	i;
	int	j;
	int	word_len;
	int	*array_of_int;

	i = -1;
	j = -1;
	word_len = 0;
	array_of_int = malloc(sizeof(int) * cw);
	if (array_of_int == NULL)
		return (0);
	while (str[++i])
	{
		if (str[i] != sep)
			word_len++;
		if (str[i] != sep && (str[i + 1] == sep || str[i + 1] == '\0'))
		{
			array_of_int[++j] = word_len;
			word_len = 0;
		}
	}
	return (array_of_int);
}

static int	ft_cw(char const *s, char c)
{
	int	i;
	int	cw;

	i = 0;
	cw = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			cw++;
		i++;
	}
	return (cw);
}

static char	**ft_malloc_array(int i, int cw, char **array_of_words,int *int_array)
{
	while (i < cw)
	{
		array_of_words[i] = malloc(sizeof(char) * (int_array[i] + 1));
		if (array_of_words[i] == NULL)
		{
			while (--i > -1)
				free(array_of_words[i]);
			free(array_of_words);
			free(int_array);
			return (0);
		}
		array_of_words[i][int_array[i]] = '\0';
		i++;
	}
	return (array_of_words);
}

static char	**array_gen(char **array_of_words, const char *s, char c)
{
	int	i;
	int	j;
	int	cw;

	i = 0;
	cw = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			array_of_words[j][cw] = s[i];
			cw++;
		}
		if (s[i] != c && s[i + 1] == c)
		{
			j++;
			cw = 0;
		}
		i++;
	}
	return (array_of_words);
}

char	**ft_split_cmds(char const *s, char c)
{
	int		i;
	int		cw;
	char	**array_of_words;
	int		*int_array;

	if (!s)
		return (0);
	i = 0;
	cw = ft_cw(s, c);
	int_array = ft_count_size(s, cw, c);
	if (int_array == NULL)
		return (NULL);
	array_of_words = malloc(sizeof(char *) * (cw + 1));
	if (array_of_words == NULL)
	{
		free(int_array);
		return (0);
	}
	array_of_words[cw] = NULL;
	array_of_words = ft_malloc_array(i, cw, array_of_words, int_array);
	free(int_array);
	return (array_gen(array_of_words, s, c));
}
