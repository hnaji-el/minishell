/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:32:05 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 20:47:21 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/executor.h"
#include "../../includes/parser.h"

int	start_exec(t_node **head_env, t_ast **pipecmd, t_exec *exec, int num_size)
{
	pid_t	pid;
	int		ret;

	if (num_size == 1 && is_builtin1((*pipecmd)->args_val[0]) != -1)
	{
		g_exit_s = built_in((*pipecmd)->args_val, head_env, 1, *pipecmd);
		return (g_exit_s);
	}
	pipe(exec->fds);
	pid = process(head_env, *pipecmd, exec);
	if (exec->totalPipe < num_size)
	{
		exec->totalPipe = exec->totalPipe + 1;
		exec->last_fd = exec->fds[0];
		start_exec(head_env, pipecmd + 1, exec, num_size);
	}
	close(exec->fds[0]);
	waitpid(pid, &ret, 0);
	is_child("0");
	if (exec->totalPipe == num_size)
		get_return_stat(ret, 1);
	return (g_exit_s);
}

int	get_out_fd(t_redirect red, int *out_fd)
{
	int		fd;

	fd = *out_fd;
	if (red.type == RED_APPEND)
		fd = open(red.filename, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fd = open(red.filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		return (1);
	}
	if (*out_fd != 1)
		close(*out_fd);
	*out_fd = fd;
	return (0);
}

int	get_file_fd(int *last_fd, int *out_fd, t_ast *pipecmd, t_node *head_env)
{
	int			i;
	t_redirect	**reds;

	reds = pipecmd->redir;
	i = 0;
	while (i < pipecmd->redir_size)
	{
		if (reds[i]->type == RED_OUTPUT || reds[i]->type == RED_APPEND)
		{
			pipecmd->flag = 1;
			if (get_out_fd (*reds[i], out_fd) != 0)
				return (1);
		}
		else if (reds[i]->type == RED_INPUT)
		{
			if (get_in_fd(*reds[i], last_fd) != 0)
				return (1);
		}
		else
			if (get_here_doc(*reds[i], last_fd, head_env) != 0)
				return (1);
		i++;
	}
	return (0);
}

int	child_process(t_node **h_env, t_ast *p_cmd, t_exec *exec, char **cmd)
{
	int		ret;
	char	*temp;

	temp = NULL;
	ret = get_file_fd(&(exec->last_fd), &(exec->fds[1]), p_cmd, *h_env);
	if (ret)
		exit(ret);
	if (!(*cmd))
		exit (0);
	if (is_builtin(cmd[0]) == -1)
	{
		temp = find_path(cmd, -1, *h_env);
		if (temp == NULL)
			exit(print_error(cmd[0], ": command not found", 127));
		*cmd = temp;
	}
	exit(execute_cmd(h_env, exec, cmd, p_cmd));
}

int	process(t_node **head_env, t_ast *pipecmd, t_exec *exec)
{
	pid_t	pid;
	char	**cmd;

	cmd = pipecmd->args_val;
	is_child("1");
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child_process(head_env, pipecmd, exec, cmd);
	close(exec->fds[1]);
	return (pid);
}
