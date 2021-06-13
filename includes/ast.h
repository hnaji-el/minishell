
#ifndef AST_H
# define AST_H

typedef enum	e_ast_type
{
	AST_COMPOUND,
	AST_PIPELINE,
	AST_COMMAND,
}				t_ast_type;

typedef enum	e_redirect_type
{
	RED_INPUT,
	RED_OUTPUT,
	RED_APPEND
}				t_redirect_type;

typedef struct	s_redirect
{
	t_redirect_type	type;
	char			*filename;
}				t_redirect;

typedef struct	s_ast
{
	t_ast_type		type;
		/*	AST_COMPOUND  */
	struct s_ast	**comp_val;
	int				comp_size;
		/*	AST_PIPELINE  */
	struct s_ast	**pipe_val;
	int				pipe_size;
		/*	AST_COMMAND   */
	char			**args_val;
	int				args_size;
	t_redirect		**redir;
	int				redir_size;
}				t_ast;

t_ast	*init_ast(t_ast_type type);

#endif
