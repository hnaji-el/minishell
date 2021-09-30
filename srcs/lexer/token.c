/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:56:26 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/12 17:56:33 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/token.h"
#include "../../includes/main.h"

t_token	*init_token(t_token_type type, char *value)
{
	t_token	*token;

	if (value == NULL)
		put_error(errno);
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		put_error(errno);
	token->type = type;
	token->value = value;
	return (token);
}

void	put_error(int errnum)
{
	char	*str;

	str = strerror(errnum);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
