
#include "parser.h"

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
		free_args_value(ast->args_value, ast->args_size);
		while (ast->redirection_size > 0)
		{
			ast->redirection_size -= 1;
			free(ast->redirection[ast->redirection_size]->filename);
			free(ast->redirection[ast->redirection_size]);
		}
		free(ast->redirection);
		free(ast);
	}
	return (NULL);
}

t_ast		*free_ast_pipeline(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->pipeline_size > 0)
		{
			ast->pipeline_size -= 1;
			free_ast_command(ast->pipeline_value[ast->pipeline_size]);
		}
		free(ast->pipeline_value);
		free(ast);
	}
	return (NULL);
}

t_ast		*free_ast(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->compound_size > 0)
		{
			ast->compound_size -= 1;
			free_ast_pipeline(ast->compound_value[ast->compound_size]);
		}
		free(ast->compound_value);
		free(ast);
	}
	return (NULL);
}

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->cur_token = lexer_get_next_token(lexer);
	parser->prev_token = NULL;
	return (parser);
}

int			parser_expected_token(t_parser *parser, t_token_type type, t_ast *ast_cmp)
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
		return (parser_expected_token(parser, TOKEN_WORD, ast_cmp)); 
	if (parser->cur_token->type == TOKEN_EOF)
	{
		free_ast(ast_cmp);
		printf("bash: syntax error near multiline command\n");
		return (1);
	}
	return (0);
}

int			expected_token(t_parser *parser)
{
	if (parser->cur_token->type == TOKEN_SEMI ||
		parser->cur_token->type == TOKEN_PIPE ||
		parser->cur_token->type == TOKEN_SYN_ERR ||
		parser->cur_token->type == TOKEN_EOF)
		return (1);
	return (0);
}


int			parser_parse_redirection(t_parser *parser, t_ast *ast, t_ast *ast_cmp)
{
	t_redirect_type	type;

	if (parser->cur_token->type == TOKEN_GREAT)
		type = RED_OUTPUT;
	else if (parser->cur_token->type == TOKEN_LESS)
		type = RED_INPUT;
	else
		type = RED_APPEND;
	parser_expected_token(parser, parser->cur_token->type, ast_cmp);
	if (parser_expected_token(parser, TOKEN_WORD, ast_cmp))
		return (1);
	ast->redirection = ft_reallocf(ast->redirection,
		sizeof(t_redirect *) * ast->redirection_size,
		sizeof(t_redirect *) * (ast->redirection_size + 1)
		);
	ast->redirection_size += 1;
	ast->redirection[ast->redirection_size - 1] = (t_redirect *)malloc(sizeof(t_redirect));
	ast->redirection[ast->redirection_size - 1]->type = type;
	ast->redirection[ast->redirection_size - 1]->filename = parser->prev_token->value;
	return (0);
}

void		parser_parse_cmd_args(t_parser *parser, t_ast *ast, t_ast *ast_cmp)
{
	while (parser->cur_token->type == TOKEN_WORD)
	{
		ast->args_value = ft_reallocf(ast->args_value,
			sizeof(char *) * ast->args_size,
			sizeof(char *) * (ast->args_size + 1)
			);
		ast->args_size += 1;
		ast->args_value[ast->args_size - 1] = parser->cur_token->value;
		parser_expected_token(parser, TOKEN_WORD, ast_cmp);
	}
}

t_ast		*parser_parse_simple_command(t_parser *parser, t_ast *ast_cmp)
{
	t_ast	*ast;

	ast = init_ast(AST_COMMAND);
	while (!expected_token(parser))
	{
		if (parser->cur_token->type == TOKEN_WORD)
			parser_parse_cmd_args(parser, ast, ast_cmp);
		else if (parser_parse_redirection(parser, ast, ast_cmp))
			return (free_ast_command(ast));
	}
	if (parser->cur_token->type == TOKEN_SYN_ERR)
	{
		parser_expected_token(parser, TOKEN_WORD, ast_cmp);
		return (free_ast_command(ast));
	}
	return (ast);
}

t_ast		*parser_parse_pipeline(t_parser *parser, t_ast *ast_cmp)
{
	t_ast	*ast;
	t_ast	*pipeline_value;

	if (parser_expected_syn_err(parser, ast_cmp))
		return (NULL);
	ast = init_ast(AST_PIPELINE);
	if (!(pipeline_value = parser_parse_simple_command(parser, ast_cmp)))
		return (free_ast_pipeline(ast));
	ast->pipeline_value = (t_ast **)malloc(sizeof(t_ast *));
	ast->pipeline_value[0] = pipeline_value;
	ast->pipeline_size += 1;
	while (parser->cur_token->type == TOKEN_PIPE)
	{
		parser_expected_token(parser, TOKEN_PIPE, ast_cmp);
		if (parser_expected_syn_err(parser, ast_cmp))
			return (free_ast_pipeline(ast));
		if (!(pipeline_value = parser_parse_simple_command(parser, ast_cmp)))
			return (free_ast_pipeline(ast));
		ast->pipeline_value = ft_reallocf(ast->pipeline_value,
			sizeof(t_ast *) * ast->pipeline_size,
			sizeof(t_ast *) * (ast->pipeline_size + 1)
			);
		ast->pipeline_size += 1;
		ast->pipeline_value[ast->pipeline_size - 1] = pipeline_value;
	}
	return (ast);
}

t_ast		*parser_parse_compound(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*compound_value;

	if (!(compound_value = parser_parse_pipeline(parser, NULL)))
		return (NULL);
	ast = init_ast(AST_COMPOUND);
	ast->compound_value = (t_ast **)malloc(sizeof(t_ast *));
	ast->compound_value[0] = compound_value;
	ast->compound_size += 1;
	while (parser->cur_token->type == TOKEN_SEMI)
	{
		parser_expected_token(parser, TOKEN_SEMI, ast);
		if (parser->cur_token->type == TOKEN_EOF)
			break ;
		if (!(compound_value = parser_parse_pipeline(parser, ast)))
			return (NULL);
		ast->compound_value = ft_reallocf(ast->compound_value,
			sizeof(t_ast *) * ast->compound_size,
			sizeof(t_ast *) * (ast->compound_size + 1)
			);
		ast->compound_size += 1;
		ast->compound_value[ast->compound_size - 1] = compound_value;
	}
	return (ast);
}

t_ast		*parser_parse(t_parser *parser)
{
	return (parser_parse_compound(parser));
}
