
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

void	debug_here_document(t_parser *parser, t_redirect_type *type, int i)
{
	char	*value;
	char	*str;
	char	*tmp;
	int		flag;

	i += 1;
	flag = 0;
	value = ft_strdup_("");
	while (!special_meaning_chars(parser->lexer->cmd_line[i]))
	{
		printf("%c|%d\n", parser->lexer->cmd_line[i], i);
		if (parser->lexer->cmd_line[i] == '"' || parser->lexer->cmd_line[i] == '\'')
			str = collect_single_double_quotes(parser->lexer, &i, &flag);
		else
			str = collect_simple_chars(parser->lexer, &i);
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
		*type = RED_HERE_DOC_EXP;
}
