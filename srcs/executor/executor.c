
#include "../../includes/main.h"
#include "../../includes/executor.h"

int		visitor_visit_redirection(t_redirect *node)
{
	printf("REDIRECTION(%s, %d)\n", node->filename, node->type);
	return (0);
}

int		visitor_visit_command(t_ast *node, t_node *head_env)
{
	int		i;
	char	**cmd;

	cmd = malloc((node->args_size + 1) * sizeof(int) + 2);
	i = 0;
	while (i < node->redir_size)
	{
		visitor_visit_redirection(node->redir[i]);
		i++;
	}
	i = 0;
	while (i < node->args_size)
	{
		//printf("'COMMAND(%s)'\n", node->args_val[i]);
		cmd[i] = ft_strdup(node->args_val[i]);
		i++;
	}
	cmd[i] = NULL;
	start_exec(head_env, cmd, node->pipe_size);
	//printf("HELLO\n");
	// if (is_builtin1(cmd[0]))

	// temp1 = find_path(head_env, cmd, -1);
	// if (!temp1)
	// 	return(127);
	// *cmd = temp1;
	//return (execute_cmd(envp, cmd));
	return (0);
}

int		visitor_visit_pipeline(t_ast *node, t_node *head_env)
{
	int		i;
	int		ret;

	ret = 1;
	i = 0;
	while (i < node->pipe_size)
	{
		// printf("-------simple command------\n");
		ret = visitor_visit_command(node->pipe_val[i], head_env);
		i++;
	}
	return (ret);
}

int		visitor_visit_compound(t_ast *node, t_node *head_env)
{
	int		i;
	int		ret;

	ret = 1;
	i = 0;
	while (i < node->comp_size)
	{
		// printf("---------compound------\n");
		return (visitor_visit_pipeline(node->comp_val[i], head_env));
		i++;
	}
	return(ret);
}

int		visitor_visit(t_ast *node, t_node *head_env)
{
	int		ret;
	
	if (node == NULL)
		return (258);
	if (node->type == AST_COMPOUND)
		ret = visitor_visit_compound(node, head_env);
	return (0);
}
