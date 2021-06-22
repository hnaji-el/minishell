/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:00:25 by ael-kass          #+#    #+#             */
/*   Updated: 2021/06/22 13:00:27 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

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
    if (!ft_strcmp(str, "echo"))
        return (5);
    if (!ft_strcmp(str, "pwd"))
        return (6);
    if (!ft_strcmp(str, "env"))
        return (7);
    return (-1);
}

int     built_in1(char  **cmd, char **envp)
{
    int		res;
    
    if (cmd)
    {
		res = is_builtin1(cmd[0]);
		if (res == -1)
			return (-1);
    }
	if (res == 1)
		return(lbash_cd(cmd));
	
}