
#include "../../includes/parser.h"
#include "../../includes/main.h"

char	*collect_single_double_quotes(t_lexer *lexer, int *index, int *flag)
{
	char	*str;
	int		index_i;
	int		index_f;

	index_i = *index;
	while (lexer->cmd_line[*index] != '\'' && lexer->cmd_line[*index] != '"')
		(*index)++;
	index_f = *index;
	*index += 1;
	str = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	if (str == NULL)
		put_error(errno);
	*flag = 1;
	return (str);
}

char	*collect_simple_chars(t_lexer *lexer, int *index)
{
	char	*str;
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
	return (str);
}

t_redirect_type	collect_delimiter_of_here_doc(t_parser *parser, int index_i)
{
	char	*value;
	char	*str;
	char	*tmp;
	int		flag;

	index_i += 1;
	flag = 0;
	value = ft_strdup_("");
	while (!special_meaning_chars(parser->lexer->cmd_line[index_i]))
	{
		if (parser->lexer->cmd_line[index_i] == '"' || parser->lexer->cmd_line[index_i] == '\'')
			str = collect_single_double_quotes(parser->lexer, &index_i, &flag);
		else
			str = collect_simple_chars(parser->lexer, &index_i);
		tmp = ft_strjoin(value, str);
		if (tmp == NULL)
			put_error(errno);
		free(value);
		free(str);
		value = tmp;
	}
	free(parser->prev_token->value);
	parser->prev_token->value = value;
	if (flag == 0)
		return (RED_HERE_DOC_EXP);
	return (RED_HERE_DOC);
}
