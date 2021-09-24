
#include "../../includes/main.h"
#include "../../includes/executor.h"

int visitor_visit(t_ast *node, t_node *head_env)
{

	if (node == NULL)
		return (127);

	if (node->type == AST_PIPELINE)
	{
			start_exec(head_env, node->pipe_val, 1, 0, node->pipe_size);
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