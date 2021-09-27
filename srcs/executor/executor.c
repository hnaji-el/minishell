
#include "../../includes/parser.h"

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


int	printf_error(char *cmd, char *str, int	error)
{
	char	*tmp;

	tmp = ft_itoa(error);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putendl_fd(str, 2);
	free(tmp);
	errno = error;
	g_exit_s = error;
	return (error);
}