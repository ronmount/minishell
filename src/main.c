//#ifndef MINISHELL_H
//# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# define PROMPT "MINISHELL: "
# define EXPORT "declare -x "
# define FILE_RIGHTS 0664
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef DEFAULT_PATH
#  define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# endif

typedef enum e_return {
	RETURN_ERROR = -1,
	RETURN_SUCCESS = 0,
	RETURN_FALSE = 1,
	RETURN_TRUE = 2,
	RETURN_EXIT = 3
}			t_return;

typedef enum e_err_handl {
	ERR_NOT_VALID = 255,
	ERR_NUMERIC,
	ERR_TOO_ARG,
	ERR_SYNTAX,
	ERR_CMD_NOT,
	ERR_CD_FOLDER,
	ERR_FD,
	ERR_FILE
}			t_err_handl;

typedef struct s_re {
	char				*direct;
	char				*file;
	struct s_re			*next;
}				t_re;

typedef struct s_fd {
	int					in;
	int					out;
	int					err;
}				t_fd;

typedef struct s_command {
	int					pid;
	int					errnum;
	t_return			result;
	char				*cmd;
	struct s_envp		*argv;
	struct s_re			*re;
	struct s_fd			*fd;
	struct s_command	*next;
}				t_command;

typedef struct s_envp {
	char				*var;
	struct s_envp		*next;
}				t_envp;

typedef struct s_data {
	struct s_envp		*envp;
	struct s_command	*c_line;
	char				*r_line;
	int					errnum;
	char				*pwd;
	struct sigaction	response;
	struct sigaction	child;
}				t_data;

typedef struct s_parse {
	int					i;
	int					start;
	int					i_string;
	struct s_envp		*str;
}				t_parse;

typedef struct s_parser {
	char				*tmp;
	char				*token;
	struct s_command	*cmd;
	int					len;
	int					inside_echo;
	int					result;
}				t_parser;

void	ft_set_parent_interactive(void);
void	ft_set_parent_active(void);
void	ft_set_parent_heredoc(void);
void	ft_set_child_active(void);
char	*ft_skip_whitespaces(const char *s);
char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_copy(char *dst, char *src, size_t size);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_string_dup(const char *s);
char	*ft_get_substring(char const *s, size_t start, size_t len);
t_envp	*ft_lstnew(char *content);
t_envp	*ft_lstlast(t_envp *lst);
void	ft_lstadd_back(t_envp **lst, t_envp *new);
void	ft_delete_list(t_envp **lst);
t_envp	*init_envp(char **envp);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
size_t	ft_get_int_len(long n, int sign);
char	*ft_int_to_string(long n);
char	*ft_get_var(char *s);
int	ft_str_var_cmp(char *var_name, char *var_elem);
t_envp	*ft_get_envp_element(t_envp *lst, char *var);
void	ft_change_envp(t_data *data, char *var);
void	init(t_data *data, char **envp);
t_command	*ft_create_cmd_elem(void);
void	ft_init_parser(t_parser *parser, t_data *data);
void	ft_check_quote(char c, int *d_quote, int *s_quote);
int	ft_find_end_of_token(char *s, int *inside_echo);
int	ft_end_of_token(char *s, int *inside_echo);
t_re	*ft_lstnew_re(char *direct, char *file);
t_re	*ft_lstlast_re(t_re *lst);
void	ft_lstadd_back_re(t_re **lst, t_re *new);
void	ft_lstdel_re(t_re **re);
void	ft_get_re(t_data *data, t_parser *parser);
int	ft_check_cmd(t_data *data, t_parser *parser);
void	ft_inside_d_quote(t_parse *check, char *input, t_data *data);
void	ft_inside_s_quote(t_parse *check, char *input);
int	ft_check_validity(char *argv);
char	*ft_getenv(char *var, t_envp *envp_list);
void	ft_write_fd(int fd, char *s);
void	ft_write_fd_nl(int fd, char *s);
void	ft_parent_interactive_sigint(int sign);
void	ft_parent_active_sigint(int sign);
void	ft_parent_active_sigquit(int sign);
void	ft_found_dollar(t_parse *check, char *input, t_data *data);
char	*ft_prepare_output(t_envp *list);
char	*ft_get_next_token(t_parser *parser, t_data *data);
char	*ft_check_quotes_insert_var(t_parser *par, t_data *data);
char	*ft_char_in_str(const char *s, const char c);
int	ft_last_pos_in_string(char *s, char c);
void	ft_get_filter_path(char *input, char **path, char **filter);
t_envp	*ft_get_files(char *path);
size_t	ft_words_in_str(char const *s, const char c);
static void	ft_create_substrings(char const *s, const char c, char **array);
char	**ft_split(char const *s, const char c);
size_t	ft_count_of_in_str(const char *s, const char c);
char	*ft_remove_char(char *s, char c);
char	*ft_found_hash(char *input);
void	ft_add_string(t_parse *check, char *input);
char	*ft_check_dollar_in_heredoc(char *token, t_data *data);
void	ft_questionmark(t_parse *check, t_data *data);
t_return	ft_check_for_asterisk(t_parser *parser, char *input);
void	ft_free_char_array(char **array);
int	ft_pos_in_string(char *s, char c);
void	ft_swap(t_envp **first, t_envp *swap_a);
void	ft_sort_list(t_envp **envp);
char	*ft_strnstr(const char *big, const char *little, size_t len);
t_return	ft_check_element(t_envp *list, char **filter, int len, int size);
t_envp	*ft_apply_filter(t_envp *in_list, char **filter);
size_t	ft_replace_in_string(char *s, char c_replace, char c_with);
char	**ft_get_filter(char *filter);
t_envp	*ft_prepare_list(char *input);
int	ft_wildcard(t_command *cmd, char *input);
void	ft_parser_add_argv(t_data *data, t_parser *parser);
void	ft_free(void *ptr);
int	ft_len_whitespaces(const char *s);
void	ft_inside_echo(t_parser *parser);
void	ft_parser(t_data *data);
int main(int argc, char **argv, char **envp);


void	ft_set_parent_interactive(void)
{
	signal(SIGINT, &ft_parent_interactive_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_set_parent_active(void)
{
	signal(SIGINT, &ft_parent_active_sigint);
	signal(SIGQUIT, &ft_parent_active_sigquit);
}

void	ft_set_parent_heredoc(void)
{
	struct sigaction	response;

	sigemptyset(&response.sa_mask);
	response.sa_flags = SA_SIGINFO;
	response.sa_handler = &ft_parent_active_sigint;
	sigaction(SIGINT, &response, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_set_child_active(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*ft_skip_whitespaces(const char *s)
{
	if (!s)
		return (NULL);
	while (*s != '\0' && (*s == ' ' || (*s >= '\t' && *s <= '\r')))
		s++;
	return ((char *)s);
}

char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2)
{
	ssize_t		s1_len;
	char		*output;

	s1_len = ft_strlen(s1);
	output = (char *) malloc(s1_len + ft_strlen(s2) + 1);
	if (!output)
		return (NULL);
	ft_copy(output, s1, 0);
	ft_copy(&output[s1_len], s2, 0);
	if (free_s1)
		free((void *) s1);
	if (free_s2)
		free((void *) s2);
	return (output);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*ptr;
	unsigned char		value;
	size_t				i;

	if (n > 0)
	{
		i = 0;
		ptr = (unsigned char *) s;
		value = (unsigned char) c;
		while (i < n)
		{
			*ptr = value;
			ptr++;
			i++;
		}
	}
	return (s);
}

size_t	ft_copy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src && size == 0)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else if (src)
	{
		size--;
		while (i < size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

char	*ft_string_dup(const char *s)
{
	char	*output;

	output = (char *) malloc(ft_strlen(s) + 1);
	if (!output)
		return (NULL);
	ft_copy(output, (char *)s, 0);
	return (output);
}

char	*ft_get_substring(char const *s, size_t start, size_t len)
{
	char	*substring;

	if (!s)
		return (NULL);
	substring = (char *) malloc(len + 1);
	if (!substring)
		return (NULL);
	ft_copy(substring, (char *) &s[start], len + 1);
	return (substring);
}

/*
 * inits list
 */
t_envp	*ft_lstnew(char *content)
{
	t_envp	*new_element;

	new_element = (t_envp *) malloc(sizeof(t_envp));
	if (!new_element)
		return (NULL);
	new_element->var = ft_string_dup(content);
	new_element->next = NULL;
	return (new_element);
}

/*
 * finds last node
 */
t_envp	*ft_lstlast(t_envp *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
 * push new node back
 */
void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

/*
 * deletes list
 */
void	ft_delete_list(t_envp **lst)
{
	t_envp	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free((void *) tmp->var);
		free((void *) tmp);
	}
	*lst = NULL;
}

/*
 * creates list of envp variables
 */
t_envp	*init_envp(char **envp)
{
	t_envp	*output;
	int		i;

	output = ft_lstnew(envp[0]);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&output, ft_lstnew(envp[i]));
		i++;
	}
	return (output);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

size_t	ft_get_int_len(long n, int sign)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

char	*ft_int_to_string(long n)
{
	char	*output;
	long	tmp;
	size_t	i;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	tmp = (long) n * sign;
	i = ft_get_int_len(tmp, sign);
	output = (char *) malloc(i + 1);
	if (!output)
		return (NULL);
	output[i--] = '\0';
	while (tmp > 9)
	{
		output[i] = (char)(tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	output[i] = (char)(tmp % 10) + '0';
	if (sign == -1)
		output[0] = '-';
	return (output);
}

// TODO: wtf
char	*ft_get_var(char *s)
{
	int		i;

	i = 0;
	if (ft_isdigit(s[i]) || (!ft_isalpha(s[i]) && s[i] != '_'))
		return (ft_get_substring(s, 0, 1));
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r') || s[i] == '#'
		|| s[i] == '\"' || s[i] == '\'' || s[i] == '$' || s[i] == '=')
			break ;
		if (s[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	return (ft_get_substring(s, 0, i));
}

// TODO: wtf
int	ft_str_var_cmp(char *var_name, char *var_elem)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (var_name[i] != var_elem[i])
			return (0);
		i++;
	}
	if (var_elem[i] == '=' || var_elem[i] == '\0')
		return (1);
	return (0);
}

/*
 * finds node by key
 */
t_envp	*ft_get_envp_element(t_envp *lst, char *var)
{
	t_envp	*tmp;
	char	*var_name;

	tmp = lst;
	while (tmp)
	{
		var_name = ft_get_var(var);
		if (ft_str_var_cmp(var_name, tmp->var))
		{
			free((void *) var_name);
			return (tmp);
		}
		if (var_name)
			free((void *) var_name);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 * changes envp
 */
void	ft_change_envp(t_data *data, char *var)
{
	t_envp	*tmp;

	tmp = ft_get_envp_element(data->envp, var);
	if (tmp)
	{
		free((void *) tmp->var);
		tmp->var = ft_string_dup(var);
	}
	else
		ft_lstadd_back(&data->envp, ft_lstnew(var));
}

/*
 * Inits data, calling envp copier,
 * sets default path if path not exits,
 * writes PWD env var,
 * sets SHELL env var
 */
void	init(t_data *data, char **envp)
{
	char	*output;
	t_envp	*tmp_envp;

	data->c_line = NULL;
	data->r_line = NULL;
	data->errnum = 0;
	data->envp = init_envp(envp);
	tmp_envp = ft_get_envp_element(data->envp, "PATH");
	if (!tmp_envp)
		ft_change_envp(data, DEFAULT_PATH);
	tmp_envp = ft_get_envp_element(data->envp, "PWD");
	if (!tmp_envp)
	{
		output = (char *) malloc(BUFFER_SIZE);
		if (!output)
			return ;
		getcwd(output, BUFFER_SIZE);
		output = ft_realloc("PWD=", output, 0, 1);
		ft_change_envp(data, output);
		data->pwd = output;
	}
	else
		data->pwd = ft_string_dup(tmp_envp->var);
	ft_change_envp(data, "SHELL=/42-21/minishell");
}

t_command	*ft_create_cmd_elem(void)
{
	t_command	*output;

	output = (t_command *) malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	output->fd = (t_fd *) malloc(sizeof(t_fd));
	if (!output->fd)
		return (NULL);
	output->fd->in = STDIN_FILENO;
	output->fd->out = STDOUT_FILENO;
	output->fd->err = STDERR_FILENO;
	output->result = RETURN_FALSE;
	output->re = NULL;
	return (output);
}

void	ft_init_parser(t_parser *parser, t_data *data)
{
	data->c_line = ft_create_cmd_elem();
	parser->inside_echo = 0;
	parser->result = 0;
	parser->cmd = data->c_line;
	parser->tmp = data->r_line;
	parser->tmp = ft_skip_whitespaces(parser->tmp);
}

void	ft_check_quote(char c, int *d_quote, int *s_quote)
{
	if (c == '\"')
	{
		if (*d_quote == 0)
			*d_quote = 1;
		else
			*d_quote = 0;
	}
	else if (c == '\'')
	{
		if (*s_quote == 0)
			*s_quote = 1;
		else
			*s_quote = 0;
	}
}

int	ft_find_end_of_token(char *s, int *inside_echo)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		ft_check_quote(s[i], &d_quote, &s_quote);
		if (d_quote == 0 && s_quote == 0)
		{
			if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
				break ;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '&')
			{
				if (inside_echo)
					*inside_echo = 0;
				break ;
			}
		}
		i++;
	}
	return (i);
}

int	ft_end_of_token(char *s, int *inside_echo)
{
	int	i;

	i = ft_find_end_of_token(s, inside_echo);
	if (i == 0)
	{
		if (ft_strncmp(s, "<<", 2) == 0 || ft_strncmp(s, ">>", 2) == 0
			|| ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0)
			return (2);
		else
			return (1);
	}
	return (i);
}

t_re	*ft_lstnew_re(char *direct, char *file)
{
	t_re	*new_element;

	new_element = (t_re *) malloc(sizeof(t_re));
	if (!new_element)
		return (NULL);
	new_element->direct = ft_string_dup(direct);
	new_element->file = ft_string_dup(file);
	new_element->next = NULL;
	return (new_element);
}

t_re	*ft_lstlast_re(t_re *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_re(t_re **lst, t_re *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_re(*lst)->next = new;
}

void	ft_lstdel_re(t_re **re)
{
	t_re	*re_tmp;

	while (*re)
	{
		re_tmp = *re;
		*re = (*re)->next;
		free((void *) re_tmp->direct);
		free((void *) re_tmp->file);
		re_tmp->direct = NULL;
		re_tmp->file = NULL;
		free((void *) re_tmp);
		re_tmp = NULL;
	}
	*re = NULL;
}

void	ft_get_re(t_data *data, t_parser *parser)
{
	char	*file;
	char	*direct;

	direct = parser->token;
	parser->token = NULL;
	file = ft_get_next_token(parser, data);
	ft_lstadd_back_re(&parser->cmd->re, ft_lstnew_re(direct, file));
	free((void *) direct);
	free((void *) file);
}

int	ft_check_cmd(t_data *data, t_parser *parser)
{
	parser->tmp += parser->len;
	(void) data;
	if (parser->token[0] == '|')
	{
		parser->cmd->next = ft_create_cmd_elem();
		parser->cmd->result = RETURN_SUCCESS;
		parser->cmd = parser->cmd->next;
		return (RETURN_SUCCESS);
	}
	if (ft_strcmp(parser->token, "<") || (ft_strcmp(parser->token, ">"))
		|| (ft_strcmp(parser->token, "<<")) || (ft_strcmp(parser->token, ">>")))
		return (RETURN_TRUE);
	return (RETURN_FALSE);
}

void	ft_inside_d_quote(t_parse *check, char *input, t_data *data)
{
	if (check->i > 0)
		ft_add_string(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '*')
			input[check->i] = (unsigned char) 255;
		if (input[check->i] == '$')
			ft_found_dollar(check, input, data);
		if (input[check->i] == '\"')
		{
			ft_add_string(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

void	ft_inside_s_quote(t_parse *check, char *input)
{
	if (check->i > 0)
		ft_add_string(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '*')
			input[check->i] = (unsigned char) 255;
		if (input[check->i] == '\'')
		{
			ft_add_string(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	if ((argv[0] >= '0' && argv[0] <= '9') || argv[0] == '=')
		return (0);
	while (argv[i] && argv[i] != '=')
	{
		if ((argv[i] < 'A' || argv[i] > 'Z')
			&& (argv[i] < 'a' || argv[i] > 'z')
			&& (argv[i] < '0' || argv[i] > '9')
			&& argv[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_getenv(char *var, t_envp *envp_list)
{
	while (!ft_str_var_cmp(var, envp_list->var))
	{
		envp_list = envp_list->next;
		if (envp_list == NULL)
			return (NULL);
	}
	return (&envp_list->var[ft_pos_in_string(envp_list->var, '=') + 1]);
}

void	ft_write_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

void	ft_write_fd_nl(int fd, char *s)
{
	ft_write_fd(fd, s);
	write(fd, "\n", 1);
}


void	ft_parent_interactive_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_parent_active_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
}

void	ft_parent_active_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		ft_write_fd(1, "Quit\n");
	}
}


void	ft_found_dollar(t_parse *check, char *input, t_data *data)
{
	char	*tmp;

	if (check->i > 0)
		ft_add_string(check, input);
	tmp = ft_get_var(&input[check->i + 1]);
	if (ft_check_validity(tmp) == 0 && tmp[0] != '?')
		tmp[0] = '\0';
	if (ft_strncmp(tmp, "?", 1) == 0)
		ft_questionmark(check, data);
	else if (ft_strncmp(&input[check->i + 1], "\0", 1) == 0
			 || ft_strncmp(&input[check->i + 1], "\'", 1) == 1
			 || ft_strncmp(&input[check->i + 1], "\"", 1) == 1)
		ft_lstadd_back(&check->str, ft_lstnew("$"));
	else
	{
		ft_lstadd_back(&check->str, ft_lstnew(ft_getenv(tmp, data->envp)));
	}
	check->i_string++;
	check->i += ft_strlen(tmp);
	check->start = check->i + 1;
	free((void *) tmp);
}

char	*ft_prepare_output(t_envp *list)
{
	char	*output;
	t_envp	*tmp;

	tmp = list;
	output = (char *) malloc(1);
	output[0] = '\0';
	while (tmp)
	{
		output = ft_realloc(output, tmp->var, 1, 0);
		tmp = tmp->next;
	}
	ft_delete_list(&list);
	return (output);
}

char	*ft_get_next_token(t_parser *parser, t_data *data)
{
	char	*output;
	int		len;

	parser->tmp = ft_skip_whitespaces(parser->tmp);
	len = ft_end_of_token(parser->tmp, 0);
	parser->token = ft_get_substring(parser->tmp, 0, len);
	output = ft_check_quotes_insert_var(parser, data);
	free(parser->token);
	parser->token = NULL;
	parser->tmp += len;
	return (output);
}


char	*ft_check_quotes_insert_var(t_parser *par, t_data *data)
{
	t_parse	check;

	check.str = NULL;
	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (par->token[check.i])
	{
		if (par->token[check.i] == '\"')
			ft_inside_d_quote(&check, par->token, data);
		else if (par->token[check.i] == '\'')
			ft_inside_s_quote(&check, par->token);
		else if (par->token[check.i] == '$')
			ft_found_dollar(&check, par->token, data);
		check.i++;
	}
	if (check.i_string == 0)
		return (ft_string_dup(par->token));
	if (check.start != check.i)
		ft_lstadd_back(&check.str, ft_lstnew(&par->token[check.start]));
	return (ft_prepare_output(check.str));
}

char	*ft_char_in_str(const char *s, const char c)
{
	char	*tmp;

	if (!s || !c)
		return (NULL);
	tmp = (char *) s;
	while (*tmp)
	{
		if (*tmp == c)
			return ((char *)tmp);
		tmp++;
	}
	return (NULL);
}

int	ft_last_pos_in_string(char *s, char c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (i);
}

void	ft_get_filter_path(char *input, char **path, char **filter)
{
	int		slash;

	slash = ft_last_pos_in_string(input, '/');
	if (slash >= 0)
	{
		*path = ft_get_substring(input, 0, slash + 1);
		*filter = ft_string_dup(&input[slash + 1]);
	}
	else
	{
		*path = ft_string_dup(".");
		*filter = ft_string_dup(input);
	}
}

t_envp	*ft_get_files(char *path)
{
	struct dirent	*content;
	DIR				*dir;
	t_envp			*list;

	list = NULL;
	dir = opendir(path);
	if (!dir)
		return (NULL);
	content = readdir(dir);
	while (content)
	{
		if (content->d_name[0] != '.')
			ft_lstadd_back(&list, ft_lstnew(content->d_name));
		content = readdir(dir);
	}
	closedir(dir);
	free((void *) path);
	return (list);
}

size_t	ft_words_in_str(char const *s, const char c)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			word_count++;
		}
	}
	return (word_count);
}

static void	ft_create_substrings(char const *s, const char c, char **array)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			array[word_count] = ft_get_substring(s, 0, i);
			word_count++;
			s += i;
		}
	}
	array[word_count] = NULL;
}

char	**ft_split(char const *s, const char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **) malloc((ft_words_in_str(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_substrings(s, c, array);
	return (array);
}

size_t	ft_count_of_in_str(const char *s, const char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

char	*ft_remove_char(char *s, char c)
{
	char	*output;
	char	*tmp;
	int		i;
	int		count;

	count = ft_count_of_in_str(s, c);
	if (count == 0)
		return (s);
	tmp = s;
	output = (char *) malloc((ft_strlen(s) - count) + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			output[i] = *s;
			i++;
		}
		s++;
	}
	output[i] = '\0';
	free((void *) tmp);
	return (output);
}

char	*ft_found_hash(char *input)
{
	input[0] = '\0';
	return (NULL);
}

void	ft_add_string(t_parse *check, char *input)
{
	char	*tmp;

	tmp = ft_get_substring(input, check->start, check->i - check->start);
	ft_lstadd_back(&check->str, ft_lstnew(tmp));
	free((void *) tmp);
	check->i_string++;
}

char	*ft_check_dollar_in_heredoc(char *token, t_data *data)
{
	t_parse	check;

	check.str = NULL;
	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (token[check.i])
	{
		if (token[check.i] == '$')
			ft_found_dollar(&check, token, data);
		check.i++;
	}
	if (check.i_string == 0)
		return (token);
	if (check.start != check.i)
		ft_lstadd_back(&check.str, ft_lstnew(&token[check.start]));
	free(token);
	return (ft_prepare_output(check.str));
}

void	ft_questionmark(t_parse *check, t_data *data)
{
	char	*tmp2;

	tmp2 = ft_int_to_string((long) data->errnum);
	ft_lstadd_back(&check->str, ft_lstnew(tmp2));
	free((void *) tmp2);
}

t_return	ft_check_for_asterisk(t_parser *parser, char *input)
{
	if (ft_char_in_str(input, '*'))
	{
		ft_wildcard(parser->cmd, input);
		return (RETURN_TRUE);
	}
	ft_replace_in_string(input, (unsigned char) 255, '*');
	return (RETURN_FALSE);
}

void	ft_free_char_array(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
	{
		free((void *) array[i]);
		array[i] = NULL;
		i++;
	}
	free((void *) array);
	array = NULL;
}

int	ft_pos_in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	ft_swap(t_envp **first, t_envp *swap_a)
{
	t_envp	*tmp;
	t_envp	*swap_b;

	if (!first || !swap_a)
		return ;
	tmp = *first;
	while (tmp && tmp != swap_a && tmp->next != swap_a)
		tmp = tmp->next;
	swap_b = swap_a->next;
	swap_a->next = swap_b->next;
	swap_b->next = swap_a;
	if (*first == swap_a)
	{
		*first = swap_b;
	}
	else
		tmp->next = swap_b;
}

void	ft_sort_list(t_envp **envp)
{
	t_envp	*tmp;
	int		sorted;
	int		equation;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *envp;
		while (tmp && tmp->next)
		{
			equation = ft_strncmp(tmp->var, tmp->next->var,
						ft_pos_in_string(tmp->var, '='));
			if (equation > 0)
			{
				ft_swap(envp, tmp);
				sorted = 0;
			}
			else
				tmp = tmp->next;
		}
	}
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	char	*ptr;

	i = 0;
	little_len = ft_strlen(little);
	ptr = (char *) big;
	if (little_len == 0)
		return (ptr);
	if (little_len > ft_strlen(big))
		return (NULL);
	while (i + little_len <= len)
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(&big[i], little, little_len) == 0)
				return (&ptr[i]);
		}
		i++;
	}
	return (NULL);
}

t_return	ft_check_element(t_envp *list, char **filter, int len, int size)
{
	int		i;
	int		pos;
	int		var_len;
	char	*tmp;

	var_len = ft_strlen(list->var);
	i = 1;
	if (ft_strncmp(filter[0], list->var, len) != 0)
		return (RETURN_FALSE);
	pos = len;
	while (i < size)
	{
		tmp = ft_strnstr(&list->var[pos], filter[i], var_len);
		if (tmp == NULL)
			return (RETURN_FALSE);
		pos = (tmp - list->var) + ft_strlen(filter[i]);
		i++;
	}
	if (ft_strcmp(filter[size],
				&list->var[var_len - ft_strlen(filter[size])]) != 1)
		return (RETURN_FALSE);
	return (RETURN_TRUE);
}

t_envp	*ft_apply_filter(t_envp *in_list, char **filter)
{
	t_envp	*out_list;
	int		size;
	int		len;

	out_list = NULL;
	size = 0;
	while (filter[size])
		size++;
	size--;
	len = ft_strlen(filter[0]);
	while (in_list)
	{
		if (ft_check_element(in_list, filter, len, size)
			== RETURN_TRUE)
			ft_lstadd_back(&out_list, ft_lstnew(in_list->var));
		in_list = in_list->next;
	}
	return (out_list);
}

size_t	ft_replace_in_string(char *s, char c_replace, char c_with)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c_replace)
		{
			*s = c_with;
			count++;
		}
		s++;
	}
	return (count);
}

char	**ft_get_filter(char *filter)
{
	char	**output;
	int		i;

	if (filter[0] == '*')
		filter = ft_realloc("#", filter, 0, 1);
	if (filter[ft_strlen(filter) - 1] == '*')
		filter = ft_realloc(filter, "#", 1, 0);
	output = ft_split(filter, '*');
	output[0] = ft_remove_char(output[0], '#');
	i = 0;
	while (output[i])
	{
		ft_replace_in_string(output[i], (unsigned char) 255, '*');
		i++;
	}
	i--;
	output[i] = ft_remove_char(output[i], '#');
	free((void *) filter);
	return (output);
}

t_envp	*ft_prepare_list(char *input)
{
	t_envp	*full_list;
	t_envp	*new_list;
	char	**filter_array;
	char	*path;
	char	*filter;

	ft_get_filter_path(input, &path, &filter);
	full_list = ft_get_files(path);
	filter_array = ft_get_filter(filter);
	new_list = ft_apply_filter(full_list, filter_array);
	ft_free_char_array(filter_array);
	ft_delete_list(&full_list);
	return (new_list);
}

int	ft_wildcard(t_command *cmd, char *input)
{
	t_envp	*new_list;

	new_list = ft_prepare_list(input);
	ft_sort_list(&new_list);
	if (!cmd->cmd)
	{
		cmd->cmd = new_list->var;
		new_list = new_list->next;
	}
	ft_lstadd_back(&cmd->argv, new_list);
	return (RETURN_SUCCESS);
}

void	ft_parser_add_argv(t_data *data, t_parser *parser)
{
	char	*tmp;

	tmp = ft_check_quotes_insert_var(parser, data);
	if (ft_check_for_asterisk(parser, tmp) == RETURN_FALSE)
	{
		if (parser->cmd->cmd)
			ft_lstadd_back(&parser->cmd->argv, ft_lstnew(tmp));
		else
		{
			parser->cmd->cmd = ft_string_dup(tmp);
			parser->cmd->result = RETURN_SUCCESS;
		}
	}
	free((void *) tmp);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free((void *) ptr);
	ptr = NULL;
}

int	ft_len_whitespaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r')))
		i++;
	return (i);
}

void	ft_inside_echo(t_parser *parser)
{
	parser->len = ft_len_whitespaces(parser->tmp);
	if (parser->len > 0)
		parser->tmp += parser->len;
}

/*
 * foo to parse string from readline
 */
void	ft_parser(t_data *data)
{
	t_parser	parser;

	ft_init_parser(&parser, data);
	while (*parser.tmp)
	{
		parser.len = ft_end_of_token(parser.tmp, &parser.inside_echo);
		parser.token = ft_get_substring(parser.tmp, 0, parser.len);
		parser.result = ft_check_cmd(data, &parser);
		if (parser.result == RETURN_ERROR)
			break ;
		if (parser.result == RETURN_TRUE)
			ft_get_re(data, &parser);
		if (parser.result == RETURN_FALSE)
			ft_parser_add_argv(data, &parser);
		ft_free((void *) parser.token);
		if (parser.inside_echo == 0)
			parser.tmp = ft_skip_whitespaces(parser.tmp);
		else
			ft_inside_echo(&parser);
		if (ft_strcmp(parser.cmd->cmd, "echo"))
			parser.inside_echo = 1;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	init(&data, envp);
	ft_set_parent_interactive();
	while (1)
	{
		data.r_line = readline(PROMPT);
		if (data.r_line == 0)
			break ;
		if (ft_strlen(data.r_line) > 0)
			add_history(data.r_line);
		ft_parser(&data);
	}
//	ft_clear_mem(&data);
	return (data.errnum);
}