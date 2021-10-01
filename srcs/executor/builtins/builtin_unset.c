/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:44:22 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 13:56:48 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int	lbash_unset(t_node **head, char **cmd)
{
	int	i;
	int	ret;

	i = 0;
	while (cmd[++i] != NULL)
	{
		ret = delet_var(head, cmd[i]);
	}
	return (ret);
}

void	find_var(t_node **current, t_node **previous, char *cmd)
{
	char	**temp;

	while (*current)
	{
		temp = ft_split((*current)->data, '=');
		if (ft_strcmp(temp[0], cmd) == 0)
			break ;
		*previous = *current;
		*current = (*current)->next;
		if (temp)
			free_array(temp);
	}
	if (*current)
		free_array(temp);
	return ;
}

int	delet_var(t_node **head, char *cmd)
{
	t_node	*previous;
	t_node	*current;

	previous = NULL;
	current = *head;
	if (!cmd)
		return (0);
	if (*head == NULL)
		return (-1);
	previous = current;
	find_var(&current, &previous, cmd);
	if (current)
	{
		if (current != *head)
			previous->next = current->next;
		else
			*head = current->next;
		free(current->data);
		free(current);
	}
	return (0);
}

void	printlist(t_node *head)
{
	t_node	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		ft_putstr(ptr->data);
		ptr = ptr->next;
	}
}
