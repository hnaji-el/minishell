/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:36:24 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/15 09:36:33 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/main.h"

void	add_to_value(char **value, char *str)
{
	char	*fr;

	fr = *value;
	*value = ft_strjoin(*value, str);
	if (*value == NULL)
		put_error(errno);
	free(fr);
	free(str);
}

char	*lexer_collect_double_quotes(t_lexer *lexer)
{
	char	*value;

	value = ft_strdup_("");
	lexer_advance(lexer);
	while (lexer->cur_char != '"' && lexer->cur_char != '\0')
	{
		if (lexer->cur_char == '$')
			lexer_collect_env_variables(lexer, &value);
		else
			lexer_collect_simple_chars_in_double_q(lexer, &value);
	}
	if (lexer->cur_char == '\0')
	{
		free(value);
		return (NULL);
	}
	lexer_advance(lexer);
	return (value);
}

char	*lexer_collect_single_quotes(t_lexer *lexer)
{
	char	*str;
	int		index_i;
	int		index_f;

	lexer_advance(lexer);
	index_i = lexer->cur_index;
	while (lexer->cur_char != '\'' && lexer->cur_char != '\0')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	if (lexer->cur_char == '\0')
		return (NULL);
	lexer_advance(lexer);
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	return (str);
}

char	*lexer_collect_simple_chars(t_lexer *lexer)
{
	char	*str;
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (!special_meaning_chars(lexer->cur_char) && lexer->cur_char != '"' &&
			lexer->cur_char != '\'' &&
			lexer->cur_char != '$')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	return (str);
}
