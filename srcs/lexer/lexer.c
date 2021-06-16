
#include "../../includes/lexer.h"
#include "../../includes/main.h"

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*str;

	value = ft_strdup_("");
	while (!special_meaning_chars(lexer->cur_char))
	{
		if (lexer->cur_char == '"')
			str = lexer_collect_double_quotes(lexer);
		else if (lexer->cur_char == '\'')
			str = lexer_collect_single_quotes(lexer);
		else if (lexer->cur_char == '\\')
			str = lexer_collect_escape_char(lexer);
		else if (lexer->cur_char == '$')
			str = env_vars_and_word_splitting(lexer, ft_strlen(value));
		else
			str = lexer_collect_simple_chars(lexer);
		if (str == NULL)
		{
			free(value);
			return (init_token(TOKEN_SYN_ERR, ft_strdup("")));
		}
		add_to_value(&value, str);
	}
	return (init_token(TOKEN_WORD, value));
}

t_token	*lexer_collect_redirec_great(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cur_char == '>')
		return (adva_return(lexer, init_token(TOKEN_DGREAT, ft_strdup(">>"))));
	return (init_token(TOKEN_GREAT, ft_strdup(">")));
}

t_token	*adva_return(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->cur_char != '\0')
	{
		lexer_skip_whitespaces(lexer);
		if (lexer->cur_char == '|')
			return (adva_return(lexer, init_token(TOKEN_PIPE, ft_strdup("|"))));
		if (lexer->cur_char == ';')
			return (adva_return(lexer, init_token(TOKEN_SEMI, ft_strdup(";"))));
		if (lexer->cur_char == '>')
			return (lexer_collect_redirec_great(lexer));
		if (lexer->cur_char == '<')
			return (adva_return(lexer, init_token(TOKEN_LESS, ft_strdup("<"))));
		if (lexer->cur_char != '\0')
			return (lexer_collect_id(lexer));
	}
	return (init_token(TOKEN_EOF, ft_strdup("newline")));
}
