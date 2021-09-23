/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:08:32 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/23 16:09:20 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast	*fill_pipe_size_of_all_nodes(t_ast *ast)
{
	int		i;

	i = 0;
	if (ast == NULL)
		return (NULL);
	while (i < ast->pipe_size)
	{
		ast->pipe_val[i]->pipe_size = ast->pipe_size;
		i++;
	}
	return (ast);
}

t_ast	*parser_parse_pipeline(t_parser *parser, t_ast *ast)
{
	t_ast	*ast_simple_cmd;

	while (parser->cur_token->type == TOKEN_PIPE)
	{
		expected_token(parser, TOKEN_PIPE);
		ast_simple_cmd = parser_parse_simple_command(parser);
		if (ast_simple_cmd == NULL)
			return (free_ast_pipeline(ast));
		ast->pipe_val = realloc_(ast->pipe_val, sizeof(t_ast *),
				ast->pipe_size);
		ast->pipe_size += 1;
		ast->pipe_val[ast->pipe_size - 1] = ast_simple_cmd;
	}
	return (ast);
}

t_ast	*parser_parse(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*ast_simple_cmd;

	ast_simple_cmd = parser_parse_simple_command(parser);
	if (ast_simple_cmd == NULL)
		return (NULL);
	ast = init_ast(AST_PIPELINE);
	ast->pipe_val = (t_ast **)malloc(sizeof(t_ast *));
	if (ast->pipe_val == NULL)
		put_error(errno);
	ast->pipe_val[0] = ast_simple_cmd;
	ast->pipe_size += 1;
	if (parser->cur_token->type == TOKEN_PIPE)
		ast = parser_parse_pipeline(parser, ast);
	return (fill_pipe_size_of_all_nodes(ast));
}
