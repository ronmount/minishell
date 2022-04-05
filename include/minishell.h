#ifndef MINISHELL_H
# define MINISHELL_H

# include <get_next_line.h>
# include <utils.h>

# include <readline/readline.h>
# include <readline/history.h>
typedef struct s_data {
    char *query;
    char **env;
}   t_data;

#endif
