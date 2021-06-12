/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:19:57 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/06/11 13:37:38 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	put_error(int errnum)
{
	printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}

void		free_token(t_token *token)
{
	if (token != NULL)
	{
		if (token->type != TOKEN_WORD)
			free(token->value);
		free(token);
	}
}

void		free_parser(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->cmd_line);
			free(parser->lexer);
		}
		if (parser->cur_token != NULL)
		{
			if (parser->cur_token->type != TOKEN_WORD)
				free(parser->cur_token->value);
			free(parser->cur_token);
		}
		if (parser->prev_token != NULL)
		{
			if (parser->prev_token->type != TOKEN_WORD)
				free(parser->prev_token->value);
			free(parser->prev_token);
		}
		free(parser);
	}
}

void		free_args_value(char **args_value, int	args_size)
{
	while (args_size > 0)
	{
		args_size -= 1;
		free(args_value[args_size]);
	}
	free(args_value);
}

t_ast		*free_ast_command(t_ast *ast)
{
	if (ast != NULL)
	{
		free_args_value(ast->args_val, ast->args_size);
		while (ast->redir_size > 0)
		{
			ast->redir_size -= 1;
			free(ast->redir[ast->redir_size]->filename);
			free(ast->redir[ast->redir_size]);
		}
		free(ast->redir);
		free(ast);
	}
	return (NULL);
}

t_ast		*free_ast_pipeline(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->pipe_size > 0)
		{
			ast->pipe_size -= 1;
			free_ast_command(ast->pipe_val[ast->pipe_size]);
		}
		free(ast->pipe_val);
		free(ast);
	}
	return (NULL);
}

t_ast		*free_ast(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->comp_size > 0)
		{
			ast->comp_size -= 1;
			free_ast_pipeline(ast->comp_val[ast->comp_size]);
		}
		free(ast->comp_val);
		free(ast);
	}
	return (NULL);
}

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	if ((parser = (t_parser *)malloc(sizeof(t_parser))) == NULL)
		put_error(errno);
	parser->lexer = lexer;
	parser->cur_token = lexer_get_next_token(lexer);
	parser->prev_token = NULL;
	return (parser);
}

int			expected_token(t_parser *parser, t_token_type type, t_ast *ast_cmp)
{
	if (parser->cur_token->type == type)
	{
		free_token(parser->prev_token);
		parser->prev_token = parser->cur_token;
		parser->cur_token = lexer_get_next_token(parser->lexer);
		return (0);
	}
	else if (parser->cur_token->type == TOKEN_SYN_ERR)
	{
		free_ast(ast_cmp);
		printf("bash: syntax error near multiline command\n");
	}
	else
	{
		free_ast(ast_cmp);
		printf(
			"bash: syntax error near unexpected token `%s'\n",
			parser->cur_token->value
			);
	}
	return (1);
}

int			parser_expected_syn_err(t_parser *parser, t_ast *ast_cmp)
{
	if (parser->cur_token->type == TOKEN_PIPE ||
		parser->cur_token->type == TOKEN_SEMI ||
		parser->cur_token->type == TOKEN_SYN_ERR)
		return (expected_token(parser, TOKEN_WORD, ast_cmp)); 
	if (parser->cur_token->type == TOKEN_EOF)
	{
		free_ast(ast_cmp);
		printf("bash: syntax error near multiline command\n");
		return (1);
	}
	return (0);
}

int			detect_token(t_parser *parser)
{
	if (parser->cur_token->type == TOKEN_SEMI ||
		parser->cur_token->type == TOKEN_PIPE ||
		parser->cur_token->type == TOKEN_SYN_ERR ||
		parser->cur_token->type == TOKEN_EOF)
		return (1);
	return (0);
}

void		*realloc_(void *old_alloc, size_t count, size_t old_size)
{
	void	*new_allo;

	new_allo = ft_realloc(old_alloc, count * old_size, count * (old_size + 1));
	if (new_allo == NULL)
		put_error(errno);
	return (new_allo);
}

int			parser_parse_redirect(t_parser *parser, t_ast *ast, t_ast *ast_cmp)
{
	t_redirect_type	type;

	if (parser->cur_token->type == TOKEN_GREAT)
		type = RED_OUTPUT;
	else if (parser->cur_token->type == TOKEN_LESS)
		type = RED_INPUT;
	else
		type = RED_APPEND;
	expected_token(parser, parser->cur_token->type, ast_cmp);
	if (expected_token(parser, TOKEN_WORD, ast_cmp))
		return (1);
	ast->redir = realloc_(ast->redir, sizeof(t_redirect *), ast->redir_size);
	ast->redir_size += 1;
	ast->redir[ast->redir_size - 1] = (t_redirect *)malloc(sizeof(t_redirect));
	if (ast->redir[ast->redir_size - 1] == NULL)
		put_error(errno);
	ast->redir[ast->redir_size - 1]->type = type;
	ast->redir[ast->redir_size - 1]->filename = parser->prev_token->value;
	return (0);
}

void		parser_parse_cmd_args(t_parser *parser, t_ast *ast, t_ast *ast_cmp)
{
	while (parser->cur_token->type == TOKEN_WORD)
	{
		ast->args_val = realloc_(ast->args_val, sizeof(char *), ast->args_size);
		ast->args_size += 1;
		ast->args_val[ast->args_size - 1] = parser->cur_token->value;
		expected_token(parser, TOKEN_WORD, ast_cmp);
	}
}

t_ast		*parser_parse_simple_command(t_parser *parser, t_ast *ast_cmp)
{
	t_ast	*ast;

	ast = init_ast(AST_COMMAND);
	while (!detect_token(parser))
	{
		if (parser->cur_token->type == TOKEN_WORD)
			parser_parse_cmd_args(parser, ast, ast_cmp);
		else if (parser_parse_redirect(parser, ast, ast_cmp))
			return (free_ast_command(ast));
	}
	if (parser->cur_token->type == TOKEN_SYN_ERR)
	{
		expected_token(parser, TOKEN_WORD, ast_cmp);
		return (free_ast_command(ast));
	}
	return (ast);
}

t_ast		*parser_parse_pipeline(t_parser *parser, t_ast *ast_cmp)
{
	t_ast	*ast;
	t_ast	*pipe_val;

	if (parser_expected_syn_err(parser, ast_cmp))
		return (NULL);
	ast = init_ast(AST_PIPELINE);
	if (!(pipe_val = parser_parse_simple_command(parser, ast_cmp)))
		return (free_ast_pipeline(ast));
	if (!(ast->pipe_val = (t_ast **)malloc(sizeof(t_ast *))))
		put_error(errno);
	ast->pipe_val[0] = pipe_val;
	ast->pipe_size += 1;
	while (parser->cur_token->type == TOKEN_PIPE)
	{
		expected_token(parser, TOKEN_PIPE, ast_cmp);
		if (parser_expected_syn_err(parser, ast_cmp))
			return (free_ast_pipeline(ast));
		if (!(pipe_val = parser_parse_simple_command(parser, ast_cmp)))
			return (free_ast_pipeline(ast));
		ast->pipe_val = realloc_(ast->pipe_val, sizeof(t_ast *), ast->pipe_size);
		ast->pipe_size += 1;
		ast->pipe_val[ast->pipe_size - 1] = pipe_val;
	}
	return (ast);
}

t_ast		*parser_parse_compound(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*comp_val;

	if (!(comp_val = parser_parse_pipeline(parser, NULL)))
		return (NULL);
	ast = init_ast(AST_COMPOUND);
	if (!(ast->comp_val = (t_ast **)malloc(sizeof(t_ast *))))
		put_error(errno);
	ast->comp_val[0] = comp_val;
	ast->comp_size += 1;
	while (parser->cur_token->type == TOKEN_SEMI)
	{
		expected_token(parser, TOKEN_SEMI, ast);
		if (parser->cur_token->type == TOKEN_EOF)
			break ;
		if (!(comp_val = parser_parse_pipeline(parser, ast)))
			return (NULL);
		ast->comp_val = realloc_(ast->comp_val, sizeof(t_ast *),
			ast->comp_size);
		ast->comp_size += 1;
		ast->comp_val[ast->comp_size - 1] = comp_val;
	}
	return (ast);
}
