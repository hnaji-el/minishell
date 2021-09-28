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

int    is_valid(char *str)
{
    if (*str == '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int    lbash_exit(char **cmd)
{
    int     re;

    re = 0;
    if (cmd[1] == NULL)
    {
        ft_putstr_fd("exit\n", 1);
        exit(EXIT_SUCCESS);
    }
    else if (!is_valid(cmd[1]))
    {
        ft_putstr_fd("exit\n", 1);
        exit(print_error(cmd[1], ": exit: numeric argument required", 255));
    }
    else if (cmd[2] != NULL)
            print_error(NULL, "exit\nbash: exit: too many arguments", 1);
    else
    {
        ft_putstr_fd("exit\n", 1);
        re = ft_atoi(cmd[1]);
        exit(re);
    }
    return (0);
}