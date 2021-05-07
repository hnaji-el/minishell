
#include "main.h"
#include "lexer.h"

int		main(void)
{
	char	*cmd_line;
	t_token	*token;
	t_lexer	*lexer;
	int		r;

/*
 * implement our basic REPL loop
 */
	while (1)
	{
		write(2, "minishell$ ", 12); // print prompt string
		if ((r = get_next_line(0, &cmd_line)) == -1)// read input from stdin
			exit(EXIT_FAILURE);
		lexer = init_lexer(cmd_line);
		token = lexer_get_next_token(lexer);
		while (token->type != TOKEN_EOF)
		{
			printf(" TOKEN(%s, %d)\n", token->value, token->type);
			token = lexer_get_next_token(lexer);
		}
		printf(" TOKEN(%s, %d)\n", token->value, token->type);
		if (ft_strncmp(cmd_line, "exit", 5) == 0)
			break ;
		if (cmd_line[0] == '\0')// if user pressed ENTER without writing anything
			continue ;
	}
	return (0);
}
