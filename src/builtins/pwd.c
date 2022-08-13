#include "minishell.h"

//int ft_pwd(t_command *command)
int ft_pwd(char *command)
{
    char *buf;
    (void)command;

    // syntax: char *getcwd(char *buf, size_t size);
    buf = getcwd(NULL, 0); // if *buf == NULL and size == 0, then memory will be allocated dynamically (via malloc) and the size will be adjusted automatically
    printf("%s", buf); //for check
    free(buf);
    return (0);
}