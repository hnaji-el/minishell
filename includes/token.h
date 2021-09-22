/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 09:56:02 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/09/21 22:23:25 by hnaji-el         ###   ########.fr       */
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
