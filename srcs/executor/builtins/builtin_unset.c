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
	int		i;

	printf("HELLO\n")
	if (!cmd[1])
		return(0);
	//if list is empty
	if (head == NULL)
		return (-1);
	//navigate through list
	// 	current = find(cmd[1], head);
	// //	printf("VAR : %s\n", current->data);
	// 	if (current == NULL)
	// 		return (0);
	//temp = ft_split(current->data, '=');
	i = 1;
	previous = current;
	while (current != NULL && cmd[i] != NULL)
	{
		temp = ft_split(current->data, '=');
		if (!correct_var(temp[0]))
			print_error(temp[0], ": unset : not a valid is_identifier", 1);
		if (ft_strcmp(temp[0], cmd[i]) == 0)
		{
			if (current != head)
				previous->next = current->next;
			else
				head = current->next;
			free(current->data);
			free(current->next);
		 	free(current);
		}
		previous = current;
		current = current->next;
		i++;
	}
	// else
	// {
	// 	//store reference to current link
	// 	previous = current;
	// 	//move to next link
	// 	current = current->next;
	// }
	//found a match, update the link
	// if (current)
	// {
	// 	if(current != head)
	// 		previous->next = current->next;
	// 	else
	// 		head = current->next;
	// 	 free(current->data);
	// 	 free(current->next);
	// 	 free(current);
	// }
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
