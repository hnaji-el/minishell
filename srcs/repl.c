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

int	collect_and_check_cmd_line(char **cmd_line)
{
	*cmd_line = readline("AnasHamid$ ");
	if (*cmd_line == NULL)
	{
		write(2, "\033[AAnasHamid$ exit\n", 19);
		exit(0);
	}
	if (cmd_line[0][0] == '\0')
	{
		free(*cmd_line);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*cmd_line;
	t_parser	*parser;
	t_ast		*ast;
	t_node		*envp_ll;

	(void)argc;
	(void)argv;
	envp_ll = (void *)0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	envp_ll = linked_list(envp_ll, envp);
	while (1)
	{
		if (collect_and_check_cmd_line(&cmd_line) == 0)
			continue ;
		add_history(cmd_line);
		parser = init_lexer_and_parser(cmd_line, g_exit_s, envp_ll);
		ast = parser_parse(parser);
		free_parser(parser);
		visitor_visit(ast, &envp_ll);
		free_ast_pipeline(ast);
	}
	return (0);
}
