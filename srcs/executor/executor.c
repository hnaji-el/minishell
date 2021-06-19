
#include "../../includes/main.h"
#include "../../includes/executor.h"

void	visitor_visit_redirection(t_redirect *node)
{
	printf("REDIRECTION(%s, %d)\n", node->filename, node->type);
}

void	visitor_visit_command(t_ast *node, char **envp)
{
	int		i;
	char	**cmd;
	char	*temp1;
	//t_env	*env;

	cmd = malloc(node->args_size * sizeof(int));
	i = 0;
	while (i < node->redir_size)
	{
		visitor_visit_redirection(node->redir[i]);
		i++;
	}
	i = 0;
	while (i < node->args_size)
	{
		// printf("COMMAND(%s)\n", node->args_val[i]);
		cmd[i] = node->args_val[i];
		i++;
	}
	temp1 = find_path(envp, cmd, -1);
	if (!temp1)
		EXIT_FAILURE;
	printf("SD : %s\n", temp1);
	execute_cmd(temp1, envp, cmd);
}

void	visitor_visit_pipeline(t_ast *node, char **envp)
{
	int		i;

	i = 0;
	while (i < node->pipe_size)
	{
		printf("-------simple command------\n");
		visitor_visit_command(node->pipe_val[i], envp);
		i++;
	}
}

void	visitor_visit_compound(t_ast *node, char **envp)
{
	int		i;

	i = 0;
	while (i < node->comp_size)
	{
		printf("---------compound------\n");
		visitor_visit_pipeline(node->comp_val[i], envp);
		i++;
	}
}

int		visitor_visit(t_ast *node, char **envp)
{
	if (node == NULL)
		return (258);
	if (node->type == AST_COMPOUND)
		visitor_visit_compound(node, envp);
	return (0);
}
