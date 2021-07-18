
NAME = minishell

SRCS = ./srcs/repl.c \
		./srcs/visitor.c \
		./srcs/lexer/lexer.c \
		./srcs/lexer/lexer_utils.c \
		./srcs/lexer/lexer_collect_id.c \
		./srcs/lexer/lexer_collect_id1.c \
		./srcs/lexer/lexer_collect_double_q.c \
		./srcs/lexer/token.c \
		./srcs/parser/parser.c \
		./srcs/parser/parser_utils.c \
		./srcs/parser/parser_free.c \
		./srcs/parser/ast.c \
		./srcs/parser/parser_here_doc.c \
		./srcs/executor/executor.c \
		./srcs/executor/exec_cmd.c \
		./srcs/executor/start_exec.c \
		./srcs/executor/builtins/builtin_cd.c \
		./srcs/executor/builtins/builtin_echo.c \
		./srcs/executor/builtins/builtin_env.c \
		./srcs/executor/builtins/builtin_exit.c \
		./srcs/executor/builtins/builtin_export.c \
		./srcs/executor/builtins/builtin_pwd.c \
		./srcs/executor/builtins/builtin_unset.c \
		./srcs/executor/builtins/is_builtin.c \
		./srcs/executor/builtins/utils.c \
		./srcs/get_next_line/get_next_line.c \
		./srcs/get_next_line/get_next_line_utils.c

INCLUDES = ./includes/main.h \
		./includes/token.h \
		./includes/lexer.h \
		./includes/parser.h \
		./includes/ast.h \
		./includes/executor.h

LIBFT = ./srcs/libft/libft.a

READLINE_LIB_IMAC = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
			   -I /Users/$(USER)/.brew/opt/readline/include

READLINE_LIB_MAC = -lreadline -L /usr/local/opt/readline/lib \
			   -I /usr/local/opt/readline/include

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@make -C ./srcs/libft
	@gcc $(FLAGS) $(READLINE_LIB_IMAC) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	@make -C ./srcs/libft clean

fclean:
	@make -C ./srcs/libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
