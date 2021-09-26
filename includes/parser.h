/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 10:06:33 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/25 23:08:43 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "lexer.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*cur_token;
	t_token	*prev_token;
}				t_parser;

/*                         parser.c                           */
t_ast		*parser_parse(t_parser *parser);
t_ast		*parser_parse_pipeline(t_parser *parser, t_ast *ast);
t_ast		*fill_pipe_size_of_all_nodes(t_ast *ast);
void    	exec_here_doc(int fd, char *delimiter,
								t_red_type type, t_node *envp_ll);

/*                  parser_simple_command.c                   */
t_ast		*parser_parse_simple_command(t_parser *parser);
void		parser_parse_cmd_args(t_parser *parser, t_ast *ast);
int			parser_parse_redirect(t_parser *parser, t_ast *ast);
t_red_type	get_type_of_redirection(t_parser *parser);

/*                      parser_here_doc.c                     */
void		debug_here_document(t_parser *parser, t_red_type *type, int index);
void		skip_whitespaces(char *cmd_line, int *index);
void		collect_simple_chars(t_lexer *lexer, int *index, char **value);
void		collect_single_double_quotes(t_lexer *lexer, int *index,
				char **value, int *flag);
void		add_single_or_double_q_to_value(char **value, char c);

/*                      parser_utils.c                     */
t_parser	*init_lexer_and_parser(char *cmd_line, int exit_s, t_node *envp_ll);
int			expected_token(t_parser *parser, t_token_type type);
int			parser_check_syn_error(t_parser *parser);
void		*realloc_(void *old_alloc, size_t count, size_t old_size);

/*                       parser_free.c                        */
t_ast		*free_ast_pipeline(t_ast *ast);
t_ast		*free_ast_command(t_ast *ast);
void		free_parser(t_parser *parser);
void		free_token(t_token *token);

#endif
