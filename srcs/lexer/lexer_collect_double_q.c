
#include "../../includes/lexer.h"
#include "../../includes/main.h"

char	*ft_strdup_(char *str)
{
	char	*ptr;

	ptr = ft_strdup(str);
	if (ptr == NULL)
		put_error(errno);
	return (ptr);
}

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
	if (!(str = ft_substr(lexer->cmd_line, index_i, index_f - index_i)))
		put_error(errno);
	fr = str;
	if ((str = getenv(str)) == NULL)
		str = ft_strdup_("");
	else
		str = ft_strdup_(str);
	free(fr);
	return (str);
}

void	lexer_collect_env_variables(t_lexer *lexer, char **value)
{
	char	*str;
	char	*fr;

	lexer_advance(lexer);
	if (lexer->cur_char == '?')
	{
		str = ft_itoa(lexer->exit_status);
		if (str == NULL)
			put_error(errno);
		lexer_advance(lexer);
	}
	else if (lexer->cur_char != '_' && !ft_isalpha(lexer->cur_char))
		str = ft_strdup_("$");
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
	while (lexer->cur_char != '"' && lexer->cur_char != '\0' &&
		lexer->cur_char != '$')
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
