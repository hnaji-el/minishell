
#include "../includes/main.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

int		main(int argc, char *argv[], char *envp[])
{
	char		*cmd_line;
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	t_node		*head_env;
	int			r;
	int			exit_status;
	//int			fd = open()

	head_env = NULL;
	argc = 0;
	argv = NULL;
/*
 * implement our basic REPL loop
 */
	head_env = linked_list(head_env, envp);
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
		lexer = init_lexer(cmd_line, exit_status);
		parser = init_parser(lexer);
		ast = parser_parse_compound(parser);
		free_parser(parser);
		exit_status = visitor_visit(ast, head_env);
		free_ast(ast);
	}
	return (0);
}


//////