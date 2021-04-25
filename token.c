
#include "token.h"

t_token	*init_token(t_type_token type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}
