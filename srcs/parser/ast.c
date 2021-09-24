/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:07:30 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/23 16:07:40 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (ast == NULL)
		put_error(errno);
	ast->type = type;
	ast->pipe_val = (void *)0;
	ast->pipe_size = 0;
	ast->args_val = (void *)0;
	ast->args_size = 0;
	ast->redir = (void *)0;
	ast->redir_size = 0;
	ast->flag = 0;
	return (ast);
}
