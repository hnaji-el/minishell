
NAME = minishell

SRCS = repl.c lexer.c token.c parser.c ast.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c

INCLUDES = main.h token.h lexer.h parser.h ast.h

LIBFT = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@make -C ./libft
	@gcc $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	@make -C ./libft clean

fclean:
	@make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
