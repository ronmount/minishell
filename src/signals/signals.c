#include "minishell.h"

void	set_interactiv_exit(void)
{
	signal(SIGINT, &interactive_exit);
	signal(SIGQUIT, SIG_IGN);
}
