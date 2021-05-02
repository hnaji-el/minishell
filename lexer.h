
#ifndef LEXER_H
# define LEXER_H

# include "token.h"

typedef struct	s_lexer
{
	char	*cmd_line;
	int		cur_index;
	char	cur_char;
	int		len_cmd_line;
}				t_lexer;

t_lexer	*init_lexer(char *cmd_line);

void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer *lexer);

char	*lexer_get_cur_char_as_string(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

t_token	*lexer_collect_id(t_lexer *lexer);

char	*lexer_collect_double_quotes(t_lexer *lexer);
char	*lexer_collect_single_quotes(t_lexer *lexer);
char	*lexer_collect_escape_char(t_lexer *lexer);
char	*lexer_collect_simple_chars(t_lexer *lexer);

char	*lexer_collect_escape_char_in_double_q(t_lexer *lexer);
char	*lexer_collect_simple_chars_in_double_q(t_lexer *lexer);
#endif
