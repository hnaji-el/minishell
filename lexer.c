
#include "lexer.h"

t_lexer	*init_lexer(char *cmd_line)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer->cmd_line = cmd_line;
	lexer->cur_index = 0;
	lexer->cur_char = cmd_line[0];
	lexer->len_cmd_line = ft_strlen(cmd_line);
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->cur_char != '\0' && lexer->cur_index < lexer->len_cmd_line)
	{
		lexer->cur_index += 1;
		lexer->cur_char = lexer->cmd_line[lexer->cur_index];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->cur_char == ' ')
		lexer_advance(lexer);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->cur_char != '\0' && lexer->cur_index < lexer->len_cmd_line)
	{
		lexer_skip_whitespaces(lexer);
		if (lexer->cur_char == '|')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_cur_char_as_string(lexer))));
		if (lexer->cur_char == ';')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_cur_char_as_string(lexer))));
		if (lexer->cur_char != '\0')
			return (lexer_collect_id(lexer));
	}
	return (init_token(TOKEN_EOF, "\0"));
}

char	*lexer_get_cur_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = lexer->cur_char;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_collect_double_quotes(t_lexer *lexer)
{
	int		index_i;
	int		index_f;

	lexer_advance(lexer);
	index_i = lexer->cur_index;
	while (lexer->cur_char != '"')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	lexer_advance(lexer);
	return (ft_substr(lexer->cmd_line, index_i, index_f - index_i));
}

char	*lexer_collect_single_quotes(t_lexer *lexer)
{
	int		index_i;
	int		index_f;

	lexer_advance(lexer);
	index_i = lexer->cur_index;
	while (lexer->cur_char != '\'')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	lexer_advance(lexer);
	return (ft_substr(lexer->cmd_line, index_i, index_f - index_i));
}

char	*lexer_collect_escape_char(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	value = lexer_get_cur_char_as_string(lexer);
	lexer_advance(lexer);
	return (value);
}

int		ft_isallnum1(int c)
{
	if (c == '"' || c == '\'' || c == '\\' || c == '\0' || c == ' ')
		return (0);
	return (1);
}

char	*lexer_collect_simple_chars(t_lexer *lexer)
{
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (ft_isallnum1(lexer->cur_char))
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	return (ft_substr(lexer->cmd_line, index_i, index_f - index_i));
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*str;

	value = (char *)malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->cur_char != '\0' && lexer->cur_char != ' ' && lexer->cur_index < lexer->len_cmd_line)
	{
		if (lexer->cur_char == '"')
		{
			str = lexer_collect_double_quotes(lexer);
			value = ft_strjoin(value, str);
			continue ;
		}
		if (lexer->cur_char == '\'')
		{
			str = lexer_collect_single_quotes(lexer);
			value = ft_strjoin(value, str);
			continue ;
		}
		if (lexer->cur_char == '\\')
		{
			str = lexer_collect_escape_char(lexer);
			value = ft_strjoin(value, str);
			continue ;
		}
		str = lexer_collect_simple_chars(lexer);
		value = ft_strjoin(value, str);
	}
	return (init_token(TOKEN_ID, value));
}
