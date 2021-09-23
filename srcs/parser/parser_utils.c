/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:16:29 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/22 16:39:37 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_parser	*init_lexer_and_parser(char *cmd_line, int exit_s, t_node *envp_ll)
{
	t_lexer		*lexer;
	t_parser	*parser;

	lexer = init_lexer(cmd_line, exit_s, envp_ll);
	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		put_error(errno);
	parser->lexer = lexer;
	parser->cur_token = lexer_get_next_token(lexer);
	parser->prev_token = NULL;
	return (parser);
}

int			expected_token(t_parser *parser, t_token_type type)
{
	if (parser->cur_token->type == type)
	{
		free_token(parser->prev_token);
		parser->prev_token = parser->cur_token;
		parser->cur_token = lexer_get_next_token(parser->lexer);
		return (0);
	}
	printf("bash: syntax error near unexpected token `%s'\n",
			parser->cur_token->value);
	return (1);
}

int			parser_check_syn_error(t_parser *parser)
{
	if (parser->cur_token->type == TOKEN_PIPE
		|| parser->cur_token->type == TOKEN_EOF)
		return (expected_token(parser, TOKEN_WORD));
	return (0);
}

void		*realloc_(void *old_alloc, size_t count, size_t old_size)
{
	void	*new_allo;

	new_allo = ft_realloc(old_alloc, count * old_size, count * (old_size + 1));
	if (new_allo == NULL)
		put_error(errno);
	return (new_allo);
}
