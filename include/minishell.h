#ifndef MINISHELL_H
# define MINISHELL_H
# define BUILTIN "pwd:export:unset:env:exit:echo:cd"

# include "stdlib.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef struct s_list
{
	void			*key;
	void			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	t_list *env;
	t_list *builtin;
}	t_data;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
t_list	*add(t_list *envp, void *key, void *value);
t_list	*get_elem(t_list *envp, int elem);
t_list	*find(t_list *envp, void *key);
t_list	*split_n_save_env(char **env);
void	print_env(t_list *envp);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
t_list	*get_n(t_list *head, int n);
t_list	*read_env(char **env);
t_list	*del(t_list *head, t_list *del_node);

int		ft_pwd(char *command);
int		ft_cd(t_data *data, char *dir);
int		ft_env(t_data *data, char *command);

#endif
