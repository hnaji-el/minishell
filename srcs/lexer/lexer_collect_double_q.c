/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_double_q.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:57:15 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/20 15:32:28 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char	*collect_env_variables(t_lexer *lexer)
{
	char	*fr;
	char	*str;
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (lexer->cur_char == '_' || ft_isalnum(lexer->cur_char))
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	fr = str;
	str = ft_getenv(str, lexer->envp_ll);
	if (str == NULL)
		str = ft_strdup_("");
	free(fr);
	return (str);
}

char	*collect_exit_status(t_lexer *lexer)
{
	char	*str;

	str = ft_itoa(lexer->exit_status);
	if (str == NULL)
		put_error(errno);
	lexer_advance(lexer);
	return (str);
}

void	lexer_collect_env_variables(t_lexer *lexer, char **value)
{
	char	*str;
	char	*fr;

	lexer_advance(lexer);
	if (lexer->cur_char == '?')
		str = collect_exit_status(lexer);
	else if (lexer->cur_char != '_' && !ft_isalpha(lexer->cur_char))
	{
		str = ft_substr(lexer->cmd_line, lexer->cur_index - 1, 2);
		if (str == NULL)
			put_error(errno);
		lexer_advance(lexer);
	}
	else
		str = collect_env_variables(lexer);
	fr = *value;
	*value = ft_strjoin(*value, str);
	if (*value == NULL)
		put_error(errno);
	free(str);
	free(fr);
}

void	lexer_collect_simple_chars_in_double_q(t_lexer *lexer, char **value)
{
	char	*str;
	char	*fr;
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (lexer->cur_char != '"' && lexer->cur_char != '\0'
		&& lexer->cur_char != '$')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	if (lexer->cur_char == '\0')
		return ;
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	fr = *value;
	*value = ft_strjoin(*value, str);
	if (*value == NULL)
		put_error(errno);
	free(str);
	free(fr);
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
