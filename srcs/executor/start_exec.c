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
#include "../../includes/parser.h"

int    start_exec(t_node *head_env, t_ast **pipecmd, int index, int last_fd, int num_size)
{
    pid_t    pid;
    int      fds[2]; 
    int      ret;
    
   // printf("%s\n", (*pipecmd)->args_val[0]);
  //  exit(0);
    if (num_size == 1 && is_builtin1((*pipecmd)->args_val[0]) != -1)
        return(built_in((*pipecmd)->args_val, head_env));
    pipe(fds);
    pid = process(head_env, *pipecmd, &last_fd, index, fds);
    if (index < num_size)
        start_exec(head_env, pipecmd + 1, index + 1, fds[0], num_size);
    close(fds[0]);
    waitpid(pid, &ret, 0); 
    return (0);
}

int get_out_fd(t_redirect red, int *out_fd)
{
    int     fd;

    fd = *out_fd;
    if (red.type == RED_APPEND)
        fd = open(red.filename, O_RDWR | O_CREAT | O_APPEND, 0666);
    else
        fd = open(red.filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
        return (-1);
    if (*out_fd != 1)
        close(*out_fd);
    *out_fd = fd;
    return (0);
}

int     get_in_fd(t_redirect red, int *last_fd)
{
    int  fd;

    fd = *last_fd;
    fd = open(red.filename, O_RDONLY);
    if (fd < 0)
    {
        perror("No such file or directory\n");
        exit (EXIT_FAILURE);
    }
    if (*last_fd)
        close(*last_fd);
    *last_fd = fd;
    return (0);
}

int     get_here_doc(t_redirect red, int *last_fd, t_node *head_env)
{
    int     fd;

    fd = *last_fd;
    fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
 //   printf("")
    if (fd < 0)
    {
        perror("No such file or directory\n");
        exit (EXIT_FAILURE);
    }
    exec_here_doc(fd, red.filename, red.type, head_env);
    if (*last_fd)
        close(*last_fd);
    *last_fd = fd;
    close(*last_fd);
    *last_fd = open("/tmp/heredoc", O_RDONLY);
    return (0);
}

int     get_file_fd(int *last_fd, int *out_fd, t_ast *pipecmd, t_node *head_env)
{
    int  i;

    t_redirect **reds = pipecmd->redir;
    i = 0;
    // printf("%d\n", reds[i]->type);
    // exit(1);
    while (i < pipecmd->redir_size)
    {
        if (reds[i]->type == RED_OUTPUT || reds[i]->type == RED_APPEND)
        {
            pipecmd->flag = 1;
            get_out_fd(*reds[i], out_fd);
        }
        else if (reds[i]->type == RED_INPUT)
            get_in_fd(*reds[i], last_fd);
        else
            get_here_doc(*reds[i], last_fd, head_env);

        i++;
    }

    return (0);
}

int     process(t_node *head_env, t_ast *pipecmd, int *last_fd, int totalPipe, int fds[])
{
    pid_t   pid;
    char    *temp;
    char **cmd = pipecmd->args_val;

    pid = fork();
    temp = NULL;
    if (pid == -1)
        exit(1);
    if (pid == 0)
    { 
        get_file_fd(last_fd, &fds[1], pipecmd, head_env);
        if (!(*cmd))
            exit (127); 
        if (is_builtin(cmd[0]) == -1)
        {
            temp = find_path(cmd, -1);
            if (temp == NULL)
            {
                perror("");
                    //exit(127);
            }
            *cmd = temp;
        }
        exit(execute_cmd(head_env, *last_fd, fds, cmd, pipecmd, totalPipe));
    }
    close(fds[1]);
    return (pid);
}