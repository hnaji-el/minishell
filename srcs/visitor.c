
#include "../includes/main.h"
#include "../includes/executor.h"

int		visitor_redirection(t_redirect *node)
{
	printf("REDIRECTION(%s, %d)\n", node->filename, node->type);
	return (0);
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
		printf("command(%s)\n", node->args_val[i]);
		i++;
	}
}

void	visitor_pipeline(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->pipe_size)
	{
		printf("---------pipelines------\n");
		visitor_command(node->pipe_val[i]);
		i++;
	}
}

void	visitor_compound(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->comp_size)
	{
		printf("---------compound------\n");
		visitor_pipeline(node->comp_val[i]);
		i++;
	}
}

int		visitor_vis(t_ast *node)
{
	if (node->type == AST_COMPOUND)
		visitor_compound(node);
	return (0);
}
