
#include "../../includes/token.h"
#include "../../includes/main.h"

t_token	*init_token(t_token_type type, char *value)
{
	t_token	*token;

	if (value == NULL)
		put_error(errno);
	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
		put_error(errno);
	token->type = type;
	token->value = value;
	return (token);
}

void	put_error(int errnum)
{
	printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}
