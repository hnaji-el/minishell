/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:09:51 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/23 16:10:21 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_token(t_token *token)
{
	if (token != NULL)
	{
		if (token->type != TOKEN_WORD)
			free(token->value);
		free(token);
	}
}

void	free_parser(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->cmd_line);
			free(parser->lexer);
		}
		free_token(parser->cur_token);
		free_token(parser->prev_token);
		free(parser);
	}
}

t_ast	*free_ast_command(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->args_size-- > 0)
			free(ast->args_val[ast->args_size]);
		free(ast->args_val);
		while (ast->redir_size-- > 0)
		{
			free(ast->redir[ast->redir_size]->filename);
			free(ast->redir[ast->redir_size]);
		}
		free(ast->redir);
		free(ast);
	}
	return (NULL);
}

t_ast	*free_ast_pipeline(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->pipe_size-- > 0)
			free_ast_command(ast->pipe_val[ast->pipe_size]);
		free(ast->pipe_val);
		free(ast);
	}
	return (NULL);
}
