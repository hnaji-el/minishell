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

int    start_exec(t_node *head_env, t_ast *pipecmd, int index, int last_fd, int num_size)
{
    
    pid_t    pid;//    / node = NULL;
   // int      i;
    // if (node->redir_size != 0)
    // {
    //     while ()
    //     {
    //         /* code */
    //     }
    // }
    // printf("%s\n", );
    pipecmd->args_val[pipecmd->args_size] = NULL; // fix this hamid
    if (num_size == 1 && is_builtin1(pipecmd->args_val[0]) != -1)
        return(built_in(pipecmd->args_val, head_env));
   // pipe(fds);
    pid = process(head_env, *pipecmd, &last_fd);
    //close(fds[0]);
    if (index < num_size)
        start_exec(head_env, pipecmd + 1, index + 1, last_fd, num_size);
    waitpid(pid, 0, 0);
    return (0);
}
int get_out_fd(t_redirect red, int *out_fd)
{


    if (red.type == RED_APPEND)
        *out_fd = open(red.filename, O_CREAT | O_APPEND);
    else
        *out_fd = open(red.filename, O_CREAT );
    return (0);
}

int     get_in_fd(t_redirect red, int *last_fd)
{
    *last_fd = open(red.filename, O_RDONLY);
    return (0);
}

int     get_file_fd(int *last_fd, int *out_fd, t_ast pipecmd)
{
    int  i;

     t_redirect *reds = *(pipecmd.redir);
     printf("redir2 : %d\n", pipecmd.redir_size);
    i = 0;
    while (i < pipecmd.redir_size)
    {
        if (reds[i].type == RED_OUTPUT || reds[i].type == RED_APPEND)
            get_out_fd(reds[i], out_fd);
        else
            get_in_fd(reds[i], last_fd);
        i++;
    }
    return (0);
}

int     process(t_node *head_env, t_ast pipecmd, int *last_fd)
{
    pid_t   pid;
    char    *temp;
    char **cmd = pipecmd.args_val;   
    int     fds[2];

    pipe(fds);
    pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        if (get_file_fd(last_fd, &fds[1], pipecmd) != 0)
        {
            exit(-1);
        }
      printf("hello\n");
        if (!cmd)
            exit (127); 
        // printf("hello\n");
        if (is_builtin(cmd[0]) == -1)
        {
            temp = find_path(cmd, -1);
            if (!temp)
            {
                perror("");
                exit(127);
            }
            *cmd = temp;
            // printf("hello\n");
            printf("%s\n", *cmd);
            exit(execute_cmd(head_env, *last_fd, fds[1], cmd, pipecmd));
        }
        else
            exit(built_in(cmd, head_env));
    }
    //close(fds[1]);
    return (pid);
    // waitpid(pid, NULL, 0);
}