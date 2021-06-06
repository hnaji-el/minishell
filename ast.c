
#include "ast.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	ast->type = type;
		/*    AST_COMPOUND   */
	ast->compound_value = (void *)0;
	ast->compound_size = 0;
		/*	  AST_PIPELINE   */
	ast->pipeline_value = (void *)0;
	ast->pipeline_size = 0;
		/*    AST_COMMAND    */
	ast->args_value = (void *)0;
	ast->args_size = 0;
	ast->redirection = (void *)0;
	ast->redirection_size = 0;
	return (ast);
}
