
#include "../../includes/lexer.h"
#include "../../includes/main.h"

char	*get_word(char *env, int *index)
{
	char	*word;
	int		index_i;
	int		index_f;

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
