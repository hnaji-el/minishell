/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:40:51 by ael-kass          #+#    #+#             */
/*   Updated: 2021/06/03 18:41:09 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int     lbash_env(char **envp)
{
    int     i;
    int     a;

    t_node	*head;
	head = NULL;
    i = -1;
    a = 1;
    while (envp[++i] != NULL)
    {
        head = insert(a, envp[i], head);
		a++; 
    }
	printlist(head);
	return (0);
}


// int     main(int argc, char *argv[], char *envp[])
// {
//     argc = 0;
//     argv = NULL;
//     lbash_env(envp);
// }