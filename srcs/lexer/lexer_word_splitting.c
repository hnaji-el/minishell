/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 11:35:19 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/19 11:35:57 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/main.h"

// char	*ft_getenv(char *name, t_node *head)
// {
// 	t_node	*current;
// 	char 	**dst;
// 	char 	*value;

// 	if(head == NULL)
// 		return (NULL);
// 	current = head;
// 	while(1)
// 	{
// 		dst = ft_split(current->data, '=');
// 		if (strcmp(dst[0], name) == 0)
// 			break ;
// 		free(dst[0]);
// 		free(dst[1]);
// 		free(dst);
// 		current = current->next;
// 		if (current == NULL)
// 			return (NULL);
// 	}
// 	value = dst[1];
// 	free(dst[0]);
// 	free(dst);
// 	return (value);
// }

void	check_allocation(char *str)
{
	if (str == NULL)
		put_error(errno);
}

char	*get_next_word(char *env, int *index)
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
	word = ft_substr(env, index_i, index_f - index_i);
	if (word == NULL)
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
		word = get_next_word(env, &i);
		fr = str;
		if (n > 0 || ((env[i] == ' ' || env[i] == '\t')
			&& !special_meaning_chars(lexer->cur_char)))
		{
			str = ft_strjoin_c(str, word, ' ');
			check_allocation(str);
		}
		else
		{
			str = ft_strjoin(str, word);
			check_allocation(str);
		}
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
