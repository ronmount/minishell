SRC 	= 	src/builtins/cd.c \
            src/builtins/env.c \
            src/builtins/pwd.c \
            src/list_utils/list.c \
            src/main.c \
            src/utils/ft_bzero.c \
            src/utils/ft_calloc.c \
            src/utils/ft_split.c \
            src/utils/ft_strchr.c \
            src/utils/ft_strcmp.c \
            src/utils/ft_strdup.c \
            src/utils/ft_strlcpy.c \
            src/utils/ft_strlen.c \
            src/utils/read_env.c \
            src/utils/ft_putchar_fd.c \
            src/utils/ft_putendl_fd.c \
            src/utils/ft_putstr_fd.c \
            src/utils/ft_strjoin.c \


NAME = minishell

OBJS = ${SRC:%.c=%.o}

CC = cc -fsanitize=address # -Wall -Werror -Wextra

RM = rm -f

# -l readline
%.o:		%.c include/minishell.h
			$(CC) -I include -c $< -o $@ -g

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -l readline $(OBJS) -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	clean fclean re all