
#include "../../includes/lexer.h"
#include "../../includes/main.h"

t_lexer	*init_lexer(char *cmd_line, int exit_status)
{
	t_lexer	*lexer;

	if (!(lexer = (t_lexer *)malloc(sizeof(t_lexer))))
		put_error(errno);
	lexer->cmd_line = cmd_line;
	lexer->cur_index = 0;
	lexer->cur_char = cmd_line[0];
	lexer->exit_status = exit_status;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->cur_char != '\0')
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

t_token	*adva_return(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_collect_redirec_great(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cur_char == '>')
		return (adva_return(lexer, init_token(TOKEN_DGREAT, ft_strdup(">>"))));
	return (init_token(TOKEN_GREAT, ft_strdup(">")));
}

int		special_meaning_chars(int c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<' || c == '\0' ||
		c == ' '  || c == '\t')
		return (1);
	return (0);
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
		if (!(str = ft_strdup("")))
			put_error(errno);
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
		if ((str = ft_itoa(lexer->exit_status)) == NULL)
			put_error(errno);
		lexer_advance(lexer);
	}
	else if (lexer->cur_char != '_' && !ft_isalpha(lexer->cur_char))
	{
		if ((str = ft_strdup("$")) == NULL)
			put_error(errno);
	}
	else
		str = collect_env_variables(lexer);
	fr = *value;
	if (!(*value = ft_strjoin(*value, str)))
		put_error(errno);
	free(str);
	free(fr);
}

void	lexer_collect_escape_char_in_double_q(t_lexer *lexer, char **value)
{
	char	*str;
	char	*fr;

	lexer_advance(lexer);
	if (lexer->cur_char == '\\' || lexer->cur_char == '"' ||
		lexer->cur_char == '$')
	{
		if ((str = ft_substr(lexer->cmd_line, lexer->cur_index, 1)) == NULL)
			put_error(errno);
	}
	else
		if ((str = ft_substr(lexer->cmd_line, lexer->cur_index - 1, 2)) == NULL)
			put_error(errno);
	fr = *value;
	if (!(*value = ft_strjoin(*value, str)))
		put_error(errno);
	free(str);
	free(fr);
	lexer_advance(lexer);
}

void	lexer_collect_simple_chars_in_double_q(t_lexer *lexer, char **value)
{
	char	*str;
	char	*fr;
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (lexer->cur_char != '"' && lexer->cur_char != '\\' &&
		lexer->cur_char != '$' && lexer->cur_char != '\0')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	if (!(str = ft_substr(lexer->cmd_line, index_i, index_f - index_i)))
		put_error(errno);
	fr = *value;
	if (!(*value = ft_strjoin(*value, str)))
		put_error(errno);
	free(str);
	free(fr);
}

char	*lexer_collect_double_quotes(t_lexer *lexer)
{
	char	*value;

	if ((value = ft_strdup("")) == NULL)
		put_error(errno);
	lexer_advance(lexer);
	while (lexer->cur_char != '"' && lexer->cur_char != '\0')
	{
		if (lexer->cur_char == '\\')
			lexer_collect_escape_char_in_double_q(lexer, &value);
		else if (lexer->cur_char == '$')
			lexer_collect_env_variables(lexer, &value);
		else
			lexer_collect_simple_chars_in_double_q(lexer, &value);
	}
	if (lexer->cur_char == '\0')
	{
		free(value);
		return (NULL);
	}
	lexer_advance(lexer);
	return (value);
}

char	*lexer_collect_escape_char(t_lexer *lexer)
{
	char	*str;

	lexer_advance(lexer);
	if (lexer->cur_char == '\0')
		return (NULL);
	if ((str = ft_substr(lexer->cmd_line, lexer->cur_index, 1)) == NULL)
		put_error(errno);
	lexer_advance(lexer);
	return (str);
}

char	*lexer_collect_single_quotes(t_lexer *lexer)
{
	char	*str;
	int		index_i;
	int		index_f;

	lexer_advance(lexer);
	index_i = lexer->cur_index;
	while (lexer->cur_char != '\'' && lexer->cur_char != '\0')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	if (lexer->cur_char == '\0')
		return (NULL);
	lexer_advance(lexer);
	if ((str = ft_substr(lexer->cmd_line, index_i, index_f - index_i)) == NULL)
		put_error(errno);
	return (str);
}

char	*lexer_collect_simple_chars(t_lexer *lexer)
{
	char	*str;
	int		index_i;
	int		index_f;

	index_i = lexer->cur_index;
	while (!special_meaning_chars(lexer->cur_char) && lexer->cur_char != '"' &&
			lexer->cur_char != '\'' && lexer->cur_char != '\\' &&
			lexer->cur_char != '$')
		lexer_advance(lexer);
	index_f = lexer->cur_index;
	if ((str = ft_substr(lexer->cmd_line, index_i, index_f - index_i)) == NULL)
		put_error(errno);
	return (str);
}

char	*ft_strdup_(char *str)
{
	char	*ptr;

	ptr = ft_strdup(str);
	if (ptr == NULL)
		put_error(errno);
	return (ptr);
}

char	*get_word(char *env, int *index)
{
	int		index_i;
	int		index_f;
	char	*word;

	while (env[*index] == ' ' || env[*index] == '\t')
		*index += 1;
	index_i = *index;
	while (env[*index] != ' ' && env[*index] != '\t' && env[*index] != '\0')
		*index += 1;
	index_f = *index;
	if (!(word = ft_substr(env, index_i, index_f - index_i)))
		put_error(errno);
	return (word);
}

char	*lexer_word_splitting(t_lexer *lexer, char *env, char *str, size_t n)
{
	char	*word;
	char	*fr;
	int		i;

	i = 0;
	while (n-- > 0)
	{
		word = get_word(env, &i);
		fr = str;
		if (n > 0 || ((env[i] == ' ' || env[i] == '\t')
			&& !special_meaning_chars(lexer->cur_char)))
		{
			if (!(str = ft_strjoin_c(str, word, ' ')))
				put_error(errno);
		}
		else
			if (!(str = ft_strjoin(str, word)))
				put_error(errno);
		free(fr);
		free(word);
	}
	free(env);
	return (str);
}

char	*env_vars_and_word_splitting(t_lexer *lexer, size_t size)
{
	char	*env;
	char	*str;
	size_t	num_of_words;

	env = ft_strdup_("");
	lexer_collect_env_variables(lexer, &env);
	str = ft_strdup_("");
	num_of_words = ft_num_word(env);
	if (num_of_words == 0)
	{
		if ((env[0] == ' ' || env[0] == '\t') && size > 0 &&
			!special_meaning_chars(lexer->cur_char))
		{
			free(str);
			str = ft_strdup_(" ");
		}
		free(env);
		return (str);
	}
	if ((env[0] == ' ' || env[0] == '\t') && size > 0)
	{
		free(str);
		str = ft_strdup_(" ");
	}
	return (lexer_word_splitting(lexer, env, str, num_of_words));
}

void	add_to_value(char **value, char *str)
{
	char	*fr;

	fr = *value;
	if (!(*value = ft_strjoin(*value, str)))
		put_error(errno);
	free(fr);
	free(str);
}

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
