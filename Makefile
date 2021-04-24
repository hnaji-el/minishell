
NAME = minishell

SRCS = main.c ./get_next_line/get_next_line.c \
	   ./get_next_line/get_next_line_utils.c

INCLUDES = main.h

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
