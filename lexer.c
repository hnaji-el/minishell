
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
	while (lexer->cur_char == ' ' || lexer->cur_char == '\t')
		lexer_advance(lexer);
}

/*      ??????????????????????????????????????????????????????     */
char	*lexer_get_cur_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = lexer->cur_char;
	str[1] = '\0';
	return (str);
}
/*      ??????????????????????????????????????????????????????     */

int		special_meaning_chars(int c)
{
	if (c == '\0' || c == ' '  || c == '\t' || c == '|' || c == ';' || c == '>' || c == '<')
		return (1);
	return (0);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_collect_simple_chars_in_double_q(t_lexer *lexer)
{
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (lexer->cur_char != '"' && lexer->cur_char != '\\' && lexer->cur_char != '$')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	return (ft_substr(lexer->cmd_line, index_i, index_f - index_i));
}

char	*lexer_collect_escape_char_in_double_q(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->cur_char == '\\' || lexer->cur_char == '"' || lexer->cur_char == '$')
		value = lexer_get_cur_char_as_string(lexer);
	else
	{
		value = (char *)malloc(sizeof(char) * 3);
		value[0] = '\\';
		value[1] = lexer->cur_char;
		value[2] = '\0';
	}
	lexer_advance(lexer);
	return (value);
}

char	*lexer_collect_double_quotes(t_lexer *lexer)
{
	char	*value;
	char	*str;

	value = "";
	lexer_advance(lexer);
	while (lexer->cur_char != '"')
	{
		if (lexer->cur_char == '\\')
		{
			str = lexer_collect_escape_char_in_double_q(lexer);
			value = ft_strjoin(value, str);
			continue ;
		}
//		if (lexer->cur_char == '$')
//		{
//			str = lexer_collect_escape_char(lexer);
//			value = ft_strjoin(value, str);
//			continue ;
//		}
		str = lexer_collect_simple_chars_in_double_q(lexer);
		value = ft_strjoin(value, str);
	}
	lexer_advance(lexer);
	return (value);
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

char	*lexer_collect_simple_chars(t_lexer *lexer)
{
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (!special_meaning_chars(lexer->cur_char) && lexer->cur_char != '"' &&
			lexer->cur_char != '\'' && lexer->cur_char != '\\')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	return (ft_substr(lexer->cmd_line, index_i, index_f - index_i));
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*str;

	value = "";
	while (!special_meaning_chars(lexer->cur_char))
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

t_token	*lexer_collect_redirec_great(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cur_char == '>')
		return (lexer_advance_with_token(lexer, init_token(TOKEN_GREATGREAT, ft_strdup(">>"))));
	return (init_token(TOKEN_GREAT, ft_strdup(">")));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->cur_char != '\0')
	{
		lexer_skip_whitespaces(lexer);
		if (lexer->cur_char == '|')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_cur_char_as_string(lexer))));
		if (lexer->cur_char == ';')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_cur_char_as_string(lexer))));
		if (lexer->cur_char == '>')
			return (lexer_collect_redirec_great(lexer));
		if (lexer->cur_char == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_LESS, lexer_get_cur_char_as_string(lexer))));
		if (lexer->cur_char != '\0')
			return (lexer_collect_id(lexer));
	}
	return (init_token(TOKEN_EOF, "\0"));
}
