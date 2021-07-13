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

int     lbash_env(t_node *head_env)
{
	t_node	*ptr;
	ptr = head_env;
	//start from the beginning
	while (ptr != NULL)
	{
		if (!ft_strchr(ptr->data, '='))
			ptr = ptr->next;
		ft_putstr(ptr->data);
		write(1, "\n", 1);
		ptr = ptr->next;
	}
    return (0);
}

// int     main(int argc, char *argv[], char *envp[])
// {
//     argc = 0;
//     argv = NULL;
//     lbash_env(envp);
// }