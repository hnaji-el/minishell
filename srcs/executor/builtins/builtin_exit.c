/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:34:21 by ael-kass          #+#    #+#             */
/*   Updated: 2021/06/04 16:34:39 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int    lbash_exit(char **cmd)
{
    int     re;

    re = 0;
    if (cmd[1] == NULL)
    {
        ft_putstr_fd("exit\n", 1);
        exit(0);
        return 0;
    }
    else if (cmd[2] != NULL)
    {
        ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
        return (1);
    }
    else
    {
        ft_putstr_fd("exit\n", 1);
        re = ft_atoi(cmd[1]);
        exit(re);
    }
}

// int     main()
// {
//     while (1)
//     {
//     char *cmd[30] = {"exit"};
//     printf("%d\n", lbash_exit(cmd));
//     }
// }