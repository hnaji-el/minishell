
#include "../../includes/parser.h"
#include "../../includes/main.h"

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
	if (!(pipe_val = parser_parse_simple_command(parser, ast_cmp)))
		return (NULL);
	ast = init_ast(AST_PIPELINE);
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
		ast->pipe_val = realloc_(ast->pipe_val, sizeof(t_ast *),
			ast->pipe_size);
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
