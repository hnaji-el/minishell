
#include "../../includes/parser.h"
#include "../../includes/main.h"

char	*collect_single_double_quotes(t_lexer *lexer, int *index, int *flag)
{
	while (lexer->cmd_line[*index] != '\'' && lexer->cmd_line[*index] != '"')

}

char	*collect_simple_chars(t_lexer *lexer, int *index_i)
{
}

t_redirect_type	collect_delimiter_of_here_doc(t_lexer *lexer, int index_i)
{
	char	*value;
	char	*str;
	char	*tmp;
	int		flag;

	index_i += 1;
	flag = 0;
	value = ft_strdup_("");
	while (!special_meaning_chars(lexer->cmd_line[index_i]))
	{
		if (lexer->cmd_line[index_i] == '"' || lexer->cmd_line[index_i] == '\'')
			str = collect_single_double_quotes(lexer, &index_i, &flag);
		else
			str = collect_simple_chars(lexer, &index_i);
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
}
