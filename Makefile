SRC 	= 	src/main.c \
			src/list_utils/list.c \
			src/utils/ft_strcmp.c \
			src/utils/ft_split.c

NAME = minishell

OBJS = ${SRC:%.c=%.o}

CC = cc # -Wall -Werror -Wextra

RM = rm -f

# -l readline
%.o:		%.c include/minishell.h
			$(CC) -I include -c $< -o $@ -g

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC)  $(OBJS) -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: clean fclean re all