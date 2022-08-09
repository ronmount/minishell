#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*buf;

	while (1)
	{
		buf = readline(argv[0]);
		free(buf);
	}

	return (0);
}
