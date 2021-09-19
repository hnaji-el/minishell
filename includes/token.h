/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 09:56:02 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/18 09:56:08 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_GREAT,
	TOKEN_DGREAT,
	TOKEN_LESS,
	TOKEN_HERE_DOC,
	TOKEN_SYN_ERR,
	TOKEN_EOF
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}				t_token;

t_token	*init_token(t_token_type type, char *value);
void	put_error(int errnum);

#endif
