
#include "../../includes/parser.h"

t_red_type	get_type_of_redirection(t_parser *parser)
{
	t_red_type	type;

	if (parser->cur_token->type == TOKEN_GREAT)
		type = RED_OUTPUT;
	else if (parser->cur_token->type == TOKEN_LESS)
		type = RED_INPUT;
	else if (parser->cur_token->type == TOKEN_DGREAT)
 		type = RED_APPEND;
	else
 		type = RED_HERE_DOC;
	return (type);
}

/*	
 *	add <FILENAME> and <type> of REDIRECTION to ast_command,
 *	return 1 if not get <WORD> after <RED> (syntax error)
 *	NO Free,
 *	NO Fail
 */

int			parser_parse_redirect(t_parser *parser, t_ast *ast)
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

/*	
 *	add args(<WORD>) to ast_command,
 *	NO Free,
 *	NO Fail
 */

void		parser_parse_cmd_args(t_parser *parser, t_ast *ast)
{
	while (parser->cur_token->type == TOKEN_WORD)
	{
		ast->args_val = realloc_(ast->args_val, sizeof(char *), ast->args_size);
		ast->args_size += 1;
		ast->args_val[ast->args_size - 1] = parser->cur_token->value;
		expected_token(parser, TOKEN_WORD);
	}
}

t_ast		*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*ast;

	if (parser_check_syn_error(parser))
		return (NULL);
	ast = init_ast(AST_COMMAND);
	while (!detect_token(parser))
	{
		if (parser->cur_token->type == TOKEN_WORD)
			parser_parse_cmd_args(parser, ast);
		else if (parser_parse_redirect(parser, ast))
			return (free_ast_command(ast));
	}
	if (parser->cur_token->type == TOKEN_SYN_ERR)
	{
		expected_token(parser, TOKEN_WORD);
		return (free_ast_command(ast));
	}
	return (ast);
}

t_ast		*parser_parse_pipeline(t_parser *parser, t_ast *ast)
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

t_ast		*add_integer(t_ast *ast)
{
	int		pipe_size;
	int		i;

	i = 0;
	if (ast == NULL)
		return (NULL);
	pipe_size = ast->pipe_size;
	while (i < pipe_size)
	{
		ast->pipe_val[i]->pipe_size = pipe_size;
		i++;
	}
	return (ast);
}

t_ast		*parser_parse(t_parser *parser)
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
	return (add_integer(ast));
}
