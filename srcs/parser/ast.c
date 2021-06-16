
#include "../../includes/parser.h"
#include "../../includes/main.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*ast;

	if (!(ast = (t_ast *)malloc(sizeof(t_ast))))
		put_error(errno);
	ast->type = type;
	ast->comp_val = (void *)0;
	ast->comp_size = 0;
	ast->pipe_val = (void *)0;
	ast->pipe_size = 0;
	ast->args_val = (void *)0;
	ast->args_size = 0;
	ast->redir = (void *)0;
	ast->redir_size = 0;
	return (ast);
}
