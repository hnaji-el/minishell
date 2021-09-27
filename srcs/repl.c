/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:02:08 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/27 14:33:58 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int		visitor_vis(t_ast *ast);

void	initialize_variables(char **envp, t_node **head_env/*, int *exit_status*/)
{
	*head_env = (void *)0;
	*head_env = linked_list(*head_env, envp);
	//*exit_status = 0;
}

int	collect_and_check_cmd_line(char **cmd_line)
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
		write(2, "  \b\b\nimannnAnasHamid$ ", 22);
		free(line_buffer);
	}
	if (c == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b", 4);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*cmd_line;
 	t_parser	*parser;
 	t_ast		*ast;
 	t_node		*envp_ll;
 	//int			exit_status;

 	signal(SIGINT, sig_handler);
 	signal(SIGQUIT, sig_handler);
 	initialize_variables(envp, &envp_ll/*, &exit_status*/);
 	(void)argc;
 	(void)argv;
 	while (1)
 	{
 		if (collect_and_check_cmd_line(&cmd_line) == 0)
 			continue ;
 		add_history(cmd_line);
 		parser = init_lexer_and_parser(cmd_line, g_exit_s, envp_ll);
 		ast = parser_parse(parser);
 		free_parser(parser);
 		visitor_visit(ast, envp_ll);
 		free_ast_pipeline(ast);
 	}
 	return (0);
 }
