/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:11:49 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 17:12:44 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	visitor_visit(t_ast *node, t_node **head_env)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->last_fd = 0;
	exec->totalPipe = 1;
	if (node == NULL)
	{
		g_exit_s = 258;
		return ;
	}
	if (node->type == AST_PIPELINE)
		g_exit_s = start_exec(head_env, node->pipe_val, exec, node->pipe_size);
	free(exec);
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

int	get_in_fd(t_redirect red, int *last_fd)
{
	int		fd;

	fd = *last_fd;
	fd = open(red.filename, O_RDONLY);
	if (fd < 0)
		return (print_error(red.filename, ": No such file or directory", 1));
	if (*last_fd)
		close(*last_fd);
	*last_fd = fd;
	return (0);
}

int	get_here_doc(t_redirect red, int *last_fd, t_node *head_env)
{
	int		fd;

	fd = *last_fd;
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		write(2, "shell: Heredoc failure", 23);
		return (1);
	}
	exec_here_doc(fd, red.filename, red.type, head_env);
	if (*last_fd)
		close(*last_fd);
	*last_fd = fd;
	close(*last_fd);
	*last_fd = open("/tmp/heredoc", O_RDONLY);
	return (0);
}
