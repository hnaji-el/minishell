/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:44:22 by ael-kass          #+#    #+#             */
/*   Updated: 2021/06/03 15:44:28 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int		lbash_unset(t_node **head, char **cmd)
{
    //start from the first link
    t_node  *current = *head;
    t_node  *previous = NULL;

    //if list is empty
    if (*head == NULL)
        return (-1);
	//navigate through list
	while (ft_strcmp(current->data, cmd[1]) != 0)
	{
		//if it is last node
		if (current->next == NULL)
			return (-1);
		else
		{
			//store reference to current link
			previous = current;
			//move to next link
			current = current->next;
		}
	}
	//found a match, update the link
	if (current == *head)
		//change first to point to next link
		*head = (*head)->next;
	else
		//bypass the current link
		previous->next = current->next;

	return 0;
}

void	printlist(t_node **head)
{
	t_node	*ptr;
	ptr = *head;
	//start from the beginning
	while (ptr != NULL)
	{
		// printf("%s\n", ptr->data);
		ft_putstr(ptr->data);
		ptr = ptr->next;
	}
}


// int     main(int argc, char *argv[], char *envp[])
// {
//     int     i;
//     int     a;
//     //char    *cmd
//     char    *cmd[30] = {"export", "anass=SSD"};
//     t_node  *head;

//     i = -1;
//     a = 1;
//     // while (envp[++i] != NULL)
// 	// {
// 	// 	head = insert(a, envp[i], head);
// 	// 	a++;
//     // }
//     head = lbash_export(envp, cmd);
//     lbash_unset(&head, cmd);
// 	printlist(head);
// }