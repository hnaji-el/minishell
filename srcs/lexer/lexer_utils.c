
#include "../../includes/lexer.h"
#include "../../includes/main.h"

t_lexer	*init_lexer(char *cmd_line, int exit_status)
{
	t_lexer	*lexer;

	if (!(lexer = (t_lexer *)malloc(sizeof(t_lexer))))
		put_error(errno);
	lexer->cmd_line = cmd_line;
	lexer->cur_index = 0;
	lexer->cur_char = cmd_line[0];
	lexer->exit_status = exit_status;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->cur_char != '\0')
	{
		lexer->cur_index += 1;
		lexer->cur_char = lexer->cmd_line[lexer->cur_index];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->cur_char == ' ' || lexer->cur_char == '\t')
		lexer_advance(lexer);
}

int		special_meaning_chars(int c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<' || c == '\0' ||
		c == ' '  || c == '\t')
		return (1);
	return (0);
}
