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

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int lbash_pwd(void)
{
    char *path;

    path = getcwd(NULL, 1024);
    ft_putendl_fd(path, 1);
    free(path);
    return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
//     lbash_pwd();
//     //printf ("------SUCCESS-----");
//     return 0;
// }