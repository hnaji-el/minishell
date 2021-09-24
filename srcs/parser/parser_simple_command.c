/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 07:55:23 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/24 07:57:27 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_red_type	get_type_of_redirection(t_parser *parser)
{
	t_red_type	type;

	if (parser->cur_token->type == TOKEN_GREAT)
		type = RED_OUTPUT;
	else if (parser->cur_token->type == TOKEN_DGREAT)
		type = RED_APPEND;
	else if (parser->cur_token->type == TOKEN_LESS)
		type = RED_INPUT;
	else
		type = RED_HERE_DOC;
	return (type);
}

int	parser_parse_redirect(t_parser *parser, t_ast *ast)
{
	t_red_type	type;
	int			index_i;

	type = get_type_of_redirection(parser);
	index_i = parser->lexer->cur_index;
	expected_token(parser, parser->cur_token->type);
	if (expected_token(parser, TOKEN_WORD))
		return (1);
	ast->redir = realloc_(ast->redir, sizeof(t_redirect *), ast->redir_size);
	ast->redir_size += 1;
	ast->redir[ast->redir_size - 1] = (t_redirect *)malloc(sizeof(t_redirect));
	if (ast->redir[ast->redir_size - 1] == NULL)
		put_error(errno);
	if (type == RED_HERE_DOC)
		debug_here_document(parser, &type, index_i);
	ast->redir[ast->redir_size - 1]->type = type;
	ast->redir[ast->redir_size - 1]->filename = parser->prev_token->value;
	return (0);
}

void	parser_parse_cmd_args(t_parser *parser, t_ast *ast)
{
	while (parser->cur_token->type == TOKEN_WORD)
	{
		ast->args_val = realloc_(ast->args_val, sizeof(char *), ast->args_size);
		ast->args_size += 1;
		ast->args_val[ast->args_size - 1] = parser->cur_token->value;
		expected_token(parser, TOKEN_WORD);
	}
}

t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*ast;

	if (parser_check_syn_error(parser))
		return (NULL);
	ast = init_ast(AST_COMMAND);
	while (parser->cur_token->type != TOKEN_PIPE
		&& parser->cur_token->type != TOKEN_EOF)
	{
		if (parser->cur_token->type == TOKEN_WORD)
			parser_parse_cmd_args(parser, ast);
		else if (parser_parse_redirect(parser, ast))
			return (free_ast_command(ast));
	}
	ast->args_val = realloc_(ast->args_val, sizeof(char *), ast->args_size);
	ast->args_val[ast->args_size] = NULL;
	return (ast);
}
