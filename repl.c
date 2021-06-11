
#include "main.h"
#include "lexer.h"
#include "parser.h"

int		main(void)
{
	char		*cmd_line;
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	int			r;
	int			exit_status;

/*
 * implement our basic REPL loop
 */
 	exit_status = 0;
	while (1)
	{
		write(2, "minishell$ ", 12); // print prompt string
		if ((r = get_next_line(0, &cmd_line)) == -1)// read input from stdin
			exit(EXIT_FAILURE);
		if (cmd_line[0] == '\0')
		{
			free(cmd_line);
			continue ;
		}
		if (ft_strncmp(cmd_line, "exit", 5) == 0)
			break ;
		lexer = init_lexer(cmd_line);
		parser = init_parser(lexer);
		ast = parser_parse(parser);
		// add executor program exit_status = executor(ast);
		free_parser(parser);
		if (ast != NULL)
			free_ast(ast);
	}
	return (0);
}