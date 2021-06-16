
#include "../../includes/parser.h"
#include "../../includes/main.h"

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
		printf("bash: syntax error: unexpected end of file\n");
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
		printf("bash: syntax error: unexpected end of file\n");
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
