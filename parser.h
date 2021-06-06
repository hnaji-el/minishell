
#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "lexer.h"

typedef struct	s_parser
{
	t_lexer	*lexer;
	t_token	*cur_token;
	t_token	*prev_token;
}				t_parser;

t_parser	*init_parser(t_lexer *lexer);

t_ast		*parser_parse(t_parser *parser);
t_ast		*parser_parse_compound(t_parser *parser);
t_ast		*parser_parse_pipeline(t_parser *parser, t_ast *ast_cmp);
t_ast		*parser_parse_simple_command(t_parser *parser, t_ast *ast_cmp);
void		parser_parse_cmd_args(t_parser *parser, t_ast *ast, t_ast *ast_cmp);
int			parser_parse_redirection(t_parser *parser, t_ast *ast, t_ast *ast_cmp);

t_ast		**ft_realloc(t_ast **old_ast, int size);
char		**ft_realloc_(char **old_dptr, int size);
t_redirect	**ft_realloc__(t_redirect **old_dptr, int size);

int			parser_expected_token(t_parser *parser, t_token_type type, t_ast *ast_cmp);
int			parser_expected_syn_err(t_parser *parser, t_ast *ast_cmp);
int			expected_token(t_parser *parser);

#endif
