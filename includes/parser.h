/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 10:06:33 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/18 10:06:36 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "lexer.h"
# include "main.h"

typedef struct	s_parser
{
	t_lexer	*lexer;
	t_token	*cur_token;
	t_token	*prev_token;
}				t_parser;

t_ast		*parser_parse(t_parser *parser);
t_ast		*parser_parse_pipeline(t_parser *parser, t_ast *ast);
t_ast		*parser_parse_simple_command(t_parser *parser);
void		parser_parse_cmd_args(t_parser *parser, t_ast *ast);
int			parser_parse_redirect(t_parser *parser, t_ast *ast);
t_red_type	get_type_of_redirection(t_parser *parser);

t_ast		*free_ast_pipeline(t_ast *ast);
t_ast		*free_ast_command(t_ast *ast);
void		free_parser(t_parser *parser);
void		free_token(t_token *token);

t_parser	*init_lexer_and_parser(char *cmd_line, int exit_s/*, t_node *envp_ll*/);
int			expected_token(t_parser *parser, t_token_type type);
int			parser_expected_syn_err(t_parser *parser);
int			detect_token(t_parser *parser);
void		*realloc_(void *old_alloc, size_t count, size_t old_size);

void		debug_here_document(t_parser *parser,t_red_type *type, int index);
void		skip_whitespaces(char *cmd_line, int *index);
void		collect_simple_chars(t_lexer *lexer, int *index, char **value);
int			collect_single_double_quotes(t_lexer *lexer, int *index,
				char **value);

#endif
