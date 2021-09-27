/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:44:22 by ael-kass          #+#    #+#             */
/*   Updated: 2021/09/25 15:57:35 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int	lbash_unset(t_node *head, char **cmd)
{
	//start from the first link
	t_node  *current = head;
	t_node  *previous = NULL;
	char	**temp;

	//if list is empty
	if (head == NULL)
		return (-1);
	//navigate through list
	// 	current = find(cmd[1], head);
	// //	printf("VAR : %s\n", current->data);
	// 	if (current == NULL)
	// 		return (0);
	temp = ft_split(current->data, '=');
	while (ft_strcmp(temp[0], cmd[1]) != 0 && current->next)
	{
		//store reference to current link
		previous = current;
		//move to next link
		current = current->next;
		temp = ft_split(current->data, '=');
	}
	// else
	// {
	// 	//store reference to current link
	// 	previous = current;
	// 	//move to next link
	// 	current = current->next;
	// }
	//found a match, update the link
	if (ft_strcmp(temp[0], cmd[1]) == 0)
	{
		if(previous)
			previous->next = current->next;
		else
			head = current->next;
		free(current->data);
		free(current->next);
		free(current);
	}
	return (0);
}

void	printlist(t_node *head)
{
	t_node	*ptr;
	ptr = head;
	//start from the beginning
	while (ptr != NULL)
	{
		// printf("%s\n", ptr->data);
		ft_putstr(ptr->data);
		ptr = ptr->next;
	}
}
