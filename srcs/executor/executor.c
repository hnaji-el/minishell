
#include "../../includes/parser.h"

void	visitor_visit(t_ast *node, t_node *head_env)
{

	if (node == NULL)
	{
		g_exit_s = 258;
		return ;
	}
	if (node->type == AST_PIPELINE)
	{
			start_exec(head_env, node->pipe_val, 1, 0, node->pipe_size);
	}
}


int	print_error(char *cmd, char *str, int	error)
{
	char	*tmp;

	tmp = ft_itoa(error);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putendl_fd(str, 2);
	free(tmp);
	 g_exit_s = error;
	return (error);
}

void	get_return_stat(int ret, int flag)
{
	if (flag)
	{
		if (WIFEXITED(ret))
			g_exit_s = WEXITSTATUS(ret);
		if (WIFSIGNALED(ret))
			g_exit_s = WTERMSIG(ret) + 128;
	}
}