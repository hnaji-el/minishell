
#include "../../includes/parser.h"

int		collect_single_double_quotes(t_lexer *lexer, int *index, char **value)
{
	char	*str;
	char	*tmp;
	int		index_i;
	int		index_f;
	char	c;

	c = lexer->cmd_line[*index];
	index_i = ++(*index);
	// ATT: Add here
	if (!check_closed_quotes(lexer->cmd_line, index_i, c))
	{
		tmp = ft_strjoin_c(*value, "", c);
		if (tmp == NULL)
			put_error(errno);
		free(*value);
		*value = tmp;
		return (0);
	}
	//
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
	return (1);
}

void	collect_simple_chars(t_lexer *lexer, int *index, char **value)
{
	char	*str;
	char	*tmp;
	int		index_i;
	int		index_f;

	index_i = *index;
	while (!special_meaning_chars(lexer->cmd_line[*index]) &&
			lexer->cmd_line[*index] != '"' &&
			lexer->cmd_line[*index] != '\'')
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
			flag = collect_single_double_quotes(parser->lexer, &index, &value);
		else
			collect_simple_chars(parser->lexer, &index, &value);
	}
	free(parser->prev_token->value);
	parser->prev_token->value = value;
	if (flag == 0)
		*type = RED_HERE_DOC_EXP;
}
