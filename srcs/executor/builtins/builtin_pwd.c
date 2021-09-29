/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 11:15:08 by ael-kass          #+#    #+#             */
/*   Updated: 2021/05/24 11:15:15 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int lbash_pwd(t_node *head_env)
{
    char *path;

    path = ft_getenv("PWD", head_env);
    ft_putendl_fd(path, 1);
    free(path);
    return (0);
}

