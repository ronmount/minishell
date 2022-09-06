#include "minishell.h"

void	ft_set_exit_sig(void)
{
	signal(SIGINT, &ft_exit_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_exit_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "bye ^_^\n", 8);
		exit(0);
	}
}
