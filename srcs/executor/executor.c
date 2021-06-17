
#include "../../includes/main.h"
#include "../../includes/executor.h"

void	visitor_visit_redirection(t_redirect *node)
{
	printf("REDIRECTION(%s, %d)\n", node->filename, node->type);
}

void	visitor_visit_command(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->redir_size)
	{
		visitor_visit_redirection(node->redir[i]);
		i++;
	}
	i = 0;
	while (i < node->args_size)
	{
		printf("COMMAND(%s)\n", node->args_val[i]);
		i++;
	}
}

void	visitor_visit_pipeline(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->pipe_size)
	{
		printf("-------simple command------\n");
		visitor_visit_command(node->pipe_val[i]);
		i++;
	}
}

void	visitor_visit_compound(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->comp_size)
	{
		printf("---------compound------\n");
		visitor_visit_pipeline(node->comp_val[i]);
		i++;
	}
}

int		visitor_visit(t_ast *node)
{
	if (node == NULL)
		return (258);
	if (node->type == AST_COMPOUND)
		visitor_visit_compound(node);
	return (0);
}
