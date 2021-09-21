/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 09:58:24 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/18 09:58:27 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_ast_type
{
	AST_PIPELINE,
	AST_COMMAND,
}				t_ast_type;

typedef enum e_red_type
{
	RED_INPUT,
	RED_OUTPUT,
	RED_APPEND,
	RED_HERE_DOC,
	RED_HERE_DOC_EXP
}				t_red_type;

typedef struct s_redirect
{
	t_red_type	type;
	char		*filename;
}				t_redirect;

typedef struct s_ast
{
	t_ast_type		type;
	
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
