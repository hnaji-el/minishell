
#include "../../includes/parser.h"
#include "../../includes/main.h"

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

t_ast		*free_ast_command(t_ast *ast)
{
	if (ast != NULL)
	{
		while (ast->args_size > 0)
		{
			ast->args_size -= 1;
			free(ast->args_val[ast->args_size]);
		}
		free(ast->args_val);
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
