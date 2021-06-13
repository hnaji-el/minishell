
NAME = minishell

SRCS = ./srcs/repl.c \
		./srcs/lexer/lexer.c ./srcs/lexer/token.c \
		./srcs/parser/parser.c ./srcs/parser/parser_utils.c \
		./srcs/parser/parser_free.c ./srcs/parser/ast.c \
		./srcs/get_next_line/get_next_line.c \
		./srcs/get_next_line/get_next_line_utils.c

INCLUDES = ./includes/main.h ./includes/token.h ./includes/lexer.h \
		./includes/parser.h ./includes/ast.h

LIBFT = ./srcs/libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@make -C ./srcs/libft
	@gcc $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME) -g -fsanitize=address

clean:
	@make -C ./srcs/libft clean

fclean:
	@make -C ./srcs/libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
