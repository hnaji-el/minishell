/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 07:50:15 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/24 12:02:18 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	add_single_or_double_q_to_value(char **value, char c)
{
	char	*tmp;

	tmp = ft_strjoin_c(*value, "", c);
	if (tmp == NULL)
		put_error(errno);
	free(*value);
	*value = tmp;
	return ;
}

void	collect_single_double_quotes(t_lexer *lexer, int *index,
													char **value, int *flag)
{
	char	*str;
	char	*tmp;
	int		index_i;
	int		index_f;
	char	c;

	c = lexer->cmd_line[*index];
	index_i = ++(*index);
	if (!check_closed_quotes(lexer->cmd_line, index_i, c))
		return (add_single_or_double_q_to_value(value, c));
	while (lexer->cmd_line[*index] != c)
		(*index)++;
	index_f = *index;
	*index += 1;
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	tmp = ft_strjoin(*value, str);
	if (tmp == NULL)
		put_error(errno);
	free(*value);
	free(str);
	*value = tmp;
	*flag = 1;
}

void	collect_simple_chars(t_lexer *lexer, int *index, char **value)
{
	char	*str;
	char	*tmp;
	int		index_i;
	int		index_f;

	index_i = *index;
	while (!special_meaning_chars(lexer->cmd_line[*index])
		&& lexer->cmd_line[*index] != '"'
		&& lexer->cmd_line[*index] != '\'')
		(*index)++;
	index_f = *index;
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	tmp = ft_strjoin(*value, str);
	if (tmp == NULL)
		put_error(errno);
	free(*value);
	free(str);
	*value = tmp;
}

void	skip_whitespaces(char *cmd_line, int *index)
{
	while (cmd_line[*index] == ' ' || cmd_line[*index] == '\t')
		(*index)++;
}

void	debug_here_document(t_parser *parser, t_red_type *type, int index)
{
	char	*value;
	int		flag;

	flag = 0;
	value = ft_strdup_("");
	skip_whitespaces(parser->lexer->cmd_line, &index);
	while (!special_meaning_chars(parser->lexer->cmd_line[index]))
	{
		if (parser->lexer->cmd_line[index] == '"'
			|| parser->lexer->cmd_line[index] == '\'')
			collect_single_double_quotes(parser->lexer, &index, &value, &flag);
		else
			collect_simple_chars(parser->lexer, &index, &value);
	}
	free(parser->prev_token->value);
	parser->prev_token->value = value;
	if (flag == 0)
		*type = RED_HERE_DOC_EXP;
}
