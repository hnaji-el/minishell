
#include "../includes/main.h"
#include "../includes/executor.h"

void	visitor_redirection(t_redirect *node)
{
	printf("REDIRECTION(%s, %d)\n", node->filename, node->type);
}

void	visitor_command(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->redir_size)
	{
		visitor_redirection(node->redir[i]);
		i++;
	}
	i = 0;
	while (i < node->args_size)
	{
		printf("COMMAND(%s)\n", node->args_val[i]);
		i++;
	}
}

void	visitor_pipeline(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->pipe_size)
	{
		printf("---------pipeline------\n");
		visitor_command(node->pipe_val[i]);
		i++;
	}
}

int		visitor_vis(t_ast *node)
{
	if (node != NULL && node->type == AST_PIPELINE)
		visitor_pipeline(node);
	return (0);
}
