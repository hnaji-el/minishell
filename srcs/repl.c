
#include "../includes/main.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

int		visitor_vis(t_ast *ast);

void	initialize_variables(char **envp, t_node **head_env, int *exit_status)
{
	*head_env = (void *)0;
	*head_env = linked_list(*head_env, envp);
	*exit_status = 0;
}

int		collect_and_check_cmd_line(char **cmd_line)
{
	*cmd_line = readline("AnasHamid$ ");
	if (*cmd_line == NULL)
	{
		write(1, "\033[AAnasHamid$ exit\n", 19);
		exit(0);
	}
	if (cmd_line[0][0] == '\0')
	{
		free(*cmd_line);
		return (0);
	}
	return (1);
}

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

int		main(int argc, char **argv, char **envp)
{
	char		*cmd_line;
	t_parser	*parser;
	t_ast		*ast;
	t_node		*head_env;
	int			exit_status;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	initialize_variables(envp, &head_env, &exit_status);
	(void)argc;
	(void)argv;
	while (1)
	{
		if (collect_and_check_cmd_line(&cmd_line) == 0)
			continue ;
		add_history(cmd_line);
		parser = init_lexer_and_parser(cmd_line, exit_status);
		ast = parser_parse_compound(parser);
		free_parser(parser);
<<<<<<< HEAD
		exit_status = visitor_visit(ast, head_env, 0);
=======
		exit_status = visitor_vis(ast);
//		exit_status = visitor_visit(ast, head_env);
>>>>>>> 610599c24b2209548ff346b13d4129f44d696eb2
		free_ast(ast);
	}
	return (0);
}
