/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:32:05 by ael-kass          #+#    #+#             */
/*   Updated: 2021/07/09 18:00:31 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/executor.h"


int     in_fd(t_redirect *node_re, int *last_fd)
{
    char    *file_re;
    int     fd = *last_fd;

    file_re = node_re->filename;
    if (node_re->type == 0)
    {
        fd = open(file_re, O_RDONLY);
        if (fd < 0)
            return(-1);
        if (*last_fd)
            close(*last_fd);
        *last_fd = fd;
    }
    else
        return (1);
    return (0);
}

int     out_fd(t_redirect *node_re, int *out_fd)
{
        char *file_re;
        int     fd;

        fd = *out_fd;
        file_re = node_re->filename;
        if (file_re)
        {
            if (node_re->type == 1)
                fd = open(node_re->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (-1);
            if (*out_fd != 1)
                close(*out_fd);
            out_fd = fd;
        }
        else
            return (1);
        return (0);
}

int    start_exec(t_node *head_env, char **cmd, int num_size, t_ast *node, int last_fd)
{
    char    *temp;
    pid_t    pid;
    int     i;
    int     last_fd = 0;
    int     fds[2];

    if (num_size == 0 && is_builtin1(cmd[0]) != -1)
        return(built_in(cmd, head_env));
    pipe(fds);
    pid = process(cmd, last_fd, fds, head_env, node);
    close(fds[0]);
    waitpid(pid, NULL, 0);
    return (0);
}

int     process(char    **cmd, int  last_fd, int fds[], t_node *head_env, t_ast *node)
{
    pid_t   pid;
    char    *temp;
    int     i;
    
    pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        if (!cmd)
            exit (127);
        i = -1;
        while (node->redir[++i])
        {
            printf("node->redir");
            if (get_in_fd(node->redir[i], &last_fd) != 0 || out_fd(node->redir[i],))
            {
                printf("error redire\n");
                exit (EXIT_FAILURE);
            }
        }
        if (is_builtin(cmd[0]) == -1)
        {
            temp = find_path(cmd, -1);
            if (!temp)
            {
                perror("");
                exit(127);
            }
            *cmd = temp;
            exit(execute_cmd(head_env, cmd, last_fd));
        }
        else
            exit(built_in(cmd, head_env));
    }
    close(fds[1]);
    return (pid);
    // waitpid(pid, NULL, 0);
}