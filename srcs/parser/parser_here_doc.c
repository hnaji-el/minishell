
#include "../../includes/parser.h"
#include "../../includes/main.h"

void	collect_single_double_quotes(t_lexer *lexer, int *index, int *flag, char **value)
{
	char	*str;
	char	*fr;
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
	fr = *value;
	*value = ft_strjoin(*value, str);
	if (*value == NULL)
		put_error(errno);
	free(str);
	free(fr);
	*flag = 1;
}

void	collect_simple_chars(t_lexer *lexer, int *index, char **value)
{
	char	*str;
	char	*fr;
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
	fr = *value;
	*value = ft_strjoin(*value, str);
	if (*value == NULL)
		put_error(errno);
	free(str);
	free(fr);
}

void	skip_whitespaces(char *cmd_line, int *index)
{
	while (cmd_line[*index] == ' ' || cmd_line[*index] == '\t')
		(*index)++;
}

void	debug_here_document(t_parser *parser, t_redirect_type *type, int i)
{
	char	*value;
	int		flag;

	flag = 0;
	value = ft_strdup_("");
	skip_whitespaces(parser->lexer->cmd_line, &i);
	while (!special_meaning_chars(parser->lexer->cmd_line[i]))
	{
		if (parser->lexer->cmd_line[i] == '"' || parser->lexer->cmd_line[i] == '\'')
			collect_single_double_quotes(parser->lexer, &i, &flag, &value);
		else
			collect_simple_chars(parser->lexer, &i, &value);
	}
	free(parser->prev_token->value);
	parser->prev_token->value = value;
	if (flag == 0)
		*type = RED_HERE_DOC_EXP;
}
