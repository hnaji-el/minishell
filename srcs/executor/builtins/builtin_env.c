/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:40:51 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 13:01:28 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	lbash_env(t_node *head_env, char **cmd)
{
	t_node	*ptr;

	ptr = head_env;
	if (cmd[1] != NULL)
		exit(print_error(cmd[1], ": No such file or directory", 127));
	while (ptr != NULL)
	{
		if (ft_strchr(ptr->data, '='))
		{
			ft_putstr(ptr->data);
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
	return (0);
}
