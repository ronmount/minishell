SRCS     =  src/

OBJS     = $(SRCS:.c=.o)

CC       = gcc
RM       = rm -f
CFLAGS   = -Wall -Wextra -Werror

NAME     = minishell
INCLUDES = include/

%.o:		%.c $(INCLUDES) Makefile
			$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all:     	$(NAME)

$(NAME):	$(OBJS) $(INCLUDES) Makefile
			$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			make clean -f Makefile_bonus

fclean:		clean
			$(RM) $(NAME)
			make fclean -f Makefile_bonus

re:			fclean $(NAME)

bonus:
			make -f Makefile_bonus

.PHONY:		all clean fclean re bonus