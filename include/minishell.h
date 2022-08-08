#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdlib.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef struct s_data
{
	int	lol;
}	t_data;

typedef struct s_list
{
	void			*k;
	void			*v;
	struct s_list	*next;
}	t_list;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
t_list	*add(t_list *head, void *k, void *v);
t_list	*get_n(t_list *head, int n);

#endif
