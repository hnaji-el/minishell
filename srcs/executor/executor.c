
#include "../../includes/main.h"
#include "../../includes/executor.h"

// int		visitor_visit_redirection(t_redirect *node)
// {
// 	printf("REDIRECTION(%s, %d)\n", node->filename, node->type);
// 	return (0);
// }

// int		visitor_visit_command(t_ast *node, t_node *head_env)
// {
// 	int		i;
// //	char	**cmd;

// 	///cmd = malloc((node->args_size + 1) * sizeof(int) + 2);
// 	//i = 0;
// 	// while (i < node->redir_size)
// 	// {
// 	// 	visitor_visit_redirection(node->redir[i]);
// 	// 	i++;
// 	// }
// //	i = 0;
// 	// while (i < node->args_size)
// 	// {
// 	// 	//cmd[i] = ft_strdup(node->args_val[i]);
// 	// 	i++;
// 	// }
// //	cmd[i] = NULL;
// 	start_exec(head_env, node->args_val, node->pipe_size, node);
// 	return (0);
// }

// int		visitor_visit_pipeline(t_ast *node, t_node *head_env)
// {
// 	int		i;
// 	int		ret;

// 	ret = 1;
// 	i = 0;
// 	while (i < node->pipe_size)
// 	{
// 		ret = visitor_visit_command(node->pipe_val[i], head_env);
// 		i++;
// 	}
// 	return (ret);
// }

// int		visitor_visit_compound(t_ast *node, t_node *head_env)
// {
// 	int		i;
// 	int		ret;

// 	ret = 1;
// 	i = 0;
// 	while (i < node->comp_size)
// 	{
// 		// printf("---------compound------\n");
// 		return (visitor_visit_pipeline(node->comp_val[i], head_env));
// 		i++;
// 	}
// 	return(ret);
// }

// int		visitor_visit(t_ast *node, t_node *head_env)
// {
// 	int		ret;
	
// 	if (node == NULL)
// 		return (258);
// 	if (node->type == AST_PIPELINE)
// 		ret = visitor_visit_pipeline(node, head_env);
// 	return (0);
// }



int visitor_visit(t_ast *node, t_node *head_env)
{

	// pid_t *pid;
	
	if (node->type == AST_PIPELINE)
	{
			start_exec(head_env, *(node->pipe_val), 1, 0, node->pipe_size);
	}
	return (0);
}

// int start_exec(t_node *head_env, t_ast *pipeCmd, int index, int last_fd, envs)
// {

// 	// cd export 
	
// 	int fds[2];
// 	pipe(fds);

// 	int pid = fork();

// 	if (!pid)
// 	{
// 		//find path
// 		//populate_file_descriptors
// 		dup2(last_fd, 0);
// 		if (redir || index < *pipeCmd.pipe_size)
// 			dup2(fds[1], 1);
// 		// execute
// 	}
// 	close(fds[1]);
// 	if (index < pipeCmd[0])
// 		start_exec(pipeCmd + 1, index + 1, fds[0], envs);
// 	close(fds[0]);
// 	waitpid(pid, 0,0);
// 	return (0);
// }