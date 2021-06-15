
#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "main.h"

typedef struct	s_lexer
{
	char	*cmd_line;
	int		cur_index;
	char	cur_char;
	int		exit_status;
}				t_lexer;

t_lexer	*init_lexer(char *cmd_line, int exit_status);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*adva_return(t_lexer *lexer, t_token *token);

t_token	*lexer_collect_id(t_lexer *lexer);
char	*lexer_collect_single_quotes(t_lexer *lexer);
char	*lexer_collect_escape_char(t_lexer *lexer);
char	*lexer_collect_simple_chars(t_lexer *lexer);

char	*lexer_collect_double_quotes(t_lexer *lexer);
void	lexer_collect_escape_char_in_double_q(t_lexer *lexer, char ** value);
void	lexer_collect_simple_chars_in_double_q(t_lexer *lexer, char **value);
void	lexer_collect_env_variables(t_lexer *lexer, char **value);
char	*collect_env_variables(t_lexer *lexer);

int		special_meaning_chars(int c);
t_token	*lexer_collect_redirec_great(t_lexer *lexer);
char	*ft_strdup_(char *str);
char	*get_word(char *env, int *index);
char	*lexer_word_splitting(t_lexer *lexer, char *env, char *str, size_t n);
char	*env_vars_and_word_splitting(t_lexer *lexer, size_t size);
void	add_to_value(char **value, char *str);
#endif
