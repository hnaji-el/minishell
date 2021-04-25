
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

t_token	*lexer_collect_double_quotes(t_lexer *lexer)
{
}

t_token	*lexer_collect_single_quotes(t_lexer *lexer)
{
}

t_token	*lexer_collect_escape_char(t_lexer *lexer)
{
}

t_token	*lexer_collect_simple_chars(t_lexer *lexer)
{
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;

	while (lexer->cur_char != '\0' && lexer->cur_char != ' ')
	{
		if (lexer->cur_char == '"')
		{
			lexer_collect_double_quotes(lexer);
			// join strings.
		}
		if (lexer->cur_char == ''')
		{
			lexer_collect_single_quotes(lexer);
			// join strings.
		}
		if (lexer->cur_char == '\\')
		{
			lexer_collect_escape_char(lexer);
			// join strings.
		}
		if (lexer->cur_char != ' ')
		{
			lexer_collect_simple_chars(lexer);
			// join strings.
		}
	}
	return (init_token(TOKEN_ID, value));
}

/*
t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (ft_isalnum(lexer->cur_char))
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	value = ft_substr(lexer->cmd_line, index_i, index_f - index_i);
	return (init_token(TOKEN_ID, value));
}
*/
