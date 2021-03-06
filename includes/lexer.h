/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 09:59:51 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/24 10:49:54 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "main.h"
# include "executor.h"

typedef struct s_lexer
{
	char	*cmd_line;
	int		cur_index;
	char	cur_char;
	int		exit_status;
	t_node	*envp_ll;
}				t_lexer;

/*                  lexer.c                       */
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*adva_return(t_lexer *lexer, t_token *token);
t_token	*lexer_collect_redirec_great(t_lexer *lexer);
t_token	*lexer_collect_redirec_less(t_lexer *lexer);

/*                   lexer_collect_id.c                      */
t_token	*lexer_collect_id(t_lexer *lexer);
char	*lexer_collect_simple_chars(t_lexer *lexer);
char	*lexer_collect_single_quotes(t_lexer *lexer);
int		check_closed_quotes(char *str, int index, char c);
void	add_to_value(char **value, char *str);

/*                 lexer_collect_double_q.c                     */
char	*lexer_collect_double_quotes(t_lexer *lexer);
void	lexer_collect_simple_chars_in_double_q(t_lexer *lexer, char **value);
void	lexer_collect_env_variables(t_lexer *lexer, char **value);
char	*collect_env_variables(t_lexer *lexer);
char	*collect_exit_status(t_lexer *lexer);

/*                  lexer_word_splitting.c                  */
char	*env_vars_and_word_splitting(t_lexer *lexer, size_t size);
char	*lexer_word_splitting(t_lexer *lexer, char *env, char *str, size_t n);
char	*get_next_word(char *env, int *index);
char	*ft_getenv(char *name, t_node *head);
void	check_allocation(char *str);

/*                  lexer_utils.c                  */
t_lexer	*init_lexer(char *cmd_line, int exit_status, t_node *envp_ll);
void	lexer_skip_whitespaces(t_lexer *lexer);
void	lexer_advance(t_lexer *lexer);
int		special_meaning_chars(int c);
char	*ft_strdup_(char *str);

#endif
