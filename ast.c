
#include "ast.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	ast->type = type;
		/*    AST_COMPOUND   */
	ast->comp_val = (void *)0;
	ast->comp_size = 0;
		/*	  AST_PIPELINE   */
	ast->pipe_val = (void *)0;
	ast->pipe_size = 0;
		/*    AST_COMMAND    */
	ast->args_val = (void *)0;
	ast->args_size = 0;
	ast->redir = (void *)0;
	ast->redir_size = 0;
	return (ast);
}

void	put_error(int errnum)
{
	printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}
