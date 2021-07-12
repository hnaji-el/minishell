/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:00:25 by ael-kass          #+#    #+#             */
/*   Updated: 2021/07/09 17:32:52 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int     is_builtin(char *str)
{
    if (!ft_strcmp(str, "echo"))
        return (5);
    if (!ft_strcmp(str, "pwd"))
        return (6);
    if (!ft_strcmp(str, "env"))
        return (7);
    return (is_builtin1(str));
}

int     is_builtin1(char *str)
{
    if (!ft_strcmp(str, "cd"))
        return (1);
    if (!ft_strcmp(str, "export"))
        return (2);
    if (!ft_strcmp(str, "unset"))
        return (3);
    if (!ft_strcmp(str, "exit"))
        return (4);
    return(-1);
}

int     built_in(char  **cmd, t_node *head_env)
{
    int		res;
    
    res = 0;
    if (cmd)
    {
		res = is_builtin(cmd[0]);
		if (res == -1)
			return (-1);
    }
	if (res == 1)
		return(lbash_cd(cmd, head_env));
    if (res == 2)
        return (lbash_export(head_env, cmd));
    if (res == 3)
        return (lbash_unset(head_env, cmd));
    if (res == 4)
        return (lbash_exit(cmd));
    if (res == 5)
        return(lbash_echo(cmd));
    if (res == 6)
        return (lbash_pwd());
    if (res == 7)
        return (lbash_env(head_env));
	return (-1);
}