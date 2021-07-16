
#include "../includes/main.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

void	sig_handler(int c)
{
	char	*line_buffer;
	
	if (c == SIGINT)
	{
		line_buffer = strdup(rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		write(2, line_buffer, strlen(line_buffer));
		write(2, "  \b\b\nAnasHamid$ ", 16);
		free(line_buffer);
	}
	if (c == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b", 4);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	char		*cmd_line;
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	t_node		*head_env;
	int			exit_status;
	// int			fd;
	// fd = open("./srcs/text.txt", O_RDONLY);
/*
 * implement our basic REPL loop
 */
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	head_env = NULL;
	argc = 0;
	argv = NULL;
	head_env = linked_list(head_env, envp);
	exit_status = 0;
	while (1)
	{
		cmd_line = readline("AnasHamid$ ");
		if (cmd_line == NULL)
		{
			write(1, "\033[AAnasHamid$ exit\n", 19);
			break ;
		}
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
