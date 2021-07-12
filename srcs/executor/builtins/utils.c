/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:06:45 by ael-kass          #+#    #+#             */
/*   Updated: 2021/07/01 16:10:05 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"


t_node *linked_list(t_node *head, char **env)
{
	int		i;
    int     a;

	i = -1;
	a = 1;
	while (env[++i] != NULL)
	{
		head = insert(a, env[i], &head);
		++a;
	}
	return (head);
}