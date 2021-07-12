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

int    start_exec(t_node **head_env, char **cmd, int num_size)
{
    char    *temp;
    pid_t    pid;
    //char    **str;
    //printf("NUM_size %d\n", num_size);
    if (num_size == 0 && is_builtin1(cmd[0]) != -1)
        return(built_in(cmd, head_env));
    pid = fork();
    if (pid == -1)
        exit(1);
    if (!pid)
    {
        if (!cmd[0])
            return (127);
        if (is_builtin(cmd[0]) == -1)
        {
            temp = find_path(cmd, -1);
            if (!temp)
            {
                perror("");
                exit(127);
            }
            *cmd = temp;
            exit(execute_cmd(head_env, cmd));
        }
        else
            exit(built_in(cmd, head_env));
    }
    wait(0);
    //write(1, "HELLO\n", 6);
    return (0);
}