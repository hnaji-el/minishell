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
	int	i;
	int	ret;

	i = 0;
	while (cmd[++i] != NULL)
	{
		ret = delet_var(head, cmd[i]);
	}
	return (ret);
}

int		delet_var(t_node *head, char *cmd)
{
	t_node  *previous = NULL;
	t_node  *current = head;
	char	**temp;

	if (!cmd)
		return(0);
	if (head == NULL)
		return (-1);
	previous = current;
	while (current)
	{
		// if (current->data == NULL)
		// 	return (0);
		temp = ft_split(current->data, '=');
		if (ft_strcmp(temp[0], cmd) == 0)
			break ;
		//store reference to current link
		previous = current;
		//move to next link
		current = current->next;
	}
	//found a match, update the link
	if (current)
	{
		if(current != head)
			previous->next = current->next;
		else
			head = current->next;
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