
#ifndef TOKEN_H
# define TOKEN_H

# include "main.h"

typedef enum	e_type_token
{
	TOKEN_ID,
	TOKEN_PIPE,
	TOKEN_SEMI,
//	TOKEN_GREAT,
//	TOKEN_GREATGREAT,
//	TOKEN_LESS,
	TOKEN_EOF
}				t_type_token;

typedef struct	s_token
{
	t_type_token	type;
	char			*value;
}				t_token;

t_token	*init_token(t_type_token type, char *value);

#endif
