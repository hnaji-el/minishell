/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:32:05 by ael-kass          #+#    #+#             */
/*   Updated: 2021/06/22 13:32:10 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/executor.h"


int    start_exec(t_node *head_env, char **cmd)
{
    char    *temp;
    pid_t	pid;
	//char	**str;

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
            	return (127);
        	*cmd = temp;
        	execute_cmd(head_env, cmd);
    	}
		else
			return(built_in(cmd, head_env));
	}
	wait(0);
    //write(1, "HELLO\n", 6);
    return (0);
}