/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:53:29 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/12 17:54:15 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*lexer_collect_redirec_great(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cur_char == '>')
		return (adva_return(lexer, init_token(TOKEN_DGREAT, ft_strdup(">>"))));
	return (init_token(TOKEN_GREAT, ft_strdup(">")));
}

t_token	*lexer_collect_redirec_less(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->cur_char == '<')
		return (adva_return(lexer,
				init_token(TOKEN_HERE_DOC, ft_strdup("<<"))));
	return (init_token(TOKEN_LESS, ft_strdup("<")));
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
		if (lexer->cur_char == '>')
			return (lexer_collect_redirec_great(lexer));
		if (lexer->cur_char == '<')
			return (lexer_collect_redirec_less(lexer));
		if (lexer->cur_char != '\0')
			return (lexer_collect_id(lexer));
	}
	return (init_token(TOKEN_EOF, ft_strdup("newline")));
}
