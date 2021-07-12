/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 08:00:48 by ael-kass          #+#    #+#             */
/*   Updated: 2021/05/25 08:01:07 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

void	sort_env(t_node	*head)
{
	int    		count;
	int			i;
	int			j;
	char		*temp;
    t_node		*current;
	t_node		*next;
	
	count = lenght(head);
	i = -1;
    while (++i < count - 1)
    {
		current = head;
		next = head->next;
		j = i;
        while ( ++j < count)
		{
			if(ft_strcmp(current->data, next->data) > 0)
            {
                temp = ft_strdup(current->data);
                current->data = ft_strdup(next->data);
                next->data = ft_strdup(temp);
				free(temp);
            }
			current = current->next;
			next = next->next;
		}
    }
}

int		lenght(t_node	*current)
{
	int		lenght;
	lenght = 0;

	while (current != NULL)
	{
		current = current->next;
		lenght++;
	}
	return lenght;
}

void    printenv_expor(t_node	*head)
{
    char    **dst;
	t_node	*current;

	current = head;
	sort_env(current);
    while (current != NULL)
    {
       dst = ft_split(current->data, '=');
       ft_putstr_fd("declare -x ", 1);
       ft_putstr_fd(dst[0], 1);
	   if (dst[1])
	   {
	   		write(1, "=\"", 2);
       		ft_putstr_fd(dst[1], 1);
       		write(1, "\"", 1);
	   }
	   write(1, "\n", 1);
	   current = current->next;
    }
}

void	add_var(int n, t_node *head, char *cmd)
{
	t_node *current;
	char	**dst;
	
	if (n == 0)
		n = 1;
	current = head;
	dst = ft_split(cmd, '=');

	current = find(dst[0], head);
	//lbash_env(head);
	//printf("BEFOR ADD VAR\n");
	if (current == NULL)
		insert(n, cmd, head);
	else
		current->data = ft_strdup(cmd);
	//("data : %s\n",current->data);
	// lbash_env(current);
	// exit(0);
	//printf("After add var\n");
}
t_node	*insert(int n, char *data, t_node *head)
{
	
	t_node	*temp;
	t_node	*temp1;
	int		i;

	temp = malloc(sizeof(t_node));
	temp->data = ft_strdup(data);
	temp->next = NULL;
	if (n == 1)
	{
		temp->next = head;
		head = temp;
		return(head);
	}
	//lbash_env(&head);
	//printf("BEFOR SWAAAAAAAAP\n");
	temp1 = head;
	i = -1;
	while(temp1->next != NULL)
	{
		temp1 = temp1->next;
	}
	//temp->next = NULL;
	temp1->next = temp;
	return (head);
}

t_node	*find(char *str, t_node *head)
{
	//start from the first link
	t_node	*current = head;
	char **dst;

	// //if list is empty
	if(current == NULL)
		return NULL;
	//navigate through list
	dst = ft_split((current)->data, '=');
	while(ft_strcmp(dst[0], str) != 0)
	{
		//if it is last node
		if (current->next == NULL)
			return NULL;
		else
		{
			//go to next link
			current = current->next;
			dst = ft_split(current->data, '=');
		}
	}
	// if data found, return the current link
	return current;
}

int		lbash_export(t_node	*head_env, char **cmd)
{
	int	i;
	//int	a;
	i = 0;
	if (cmd[1] == NULL)
		printenv_expor(head_env);	
	while (cmd[++i] != NULL)
	{
		add_var(lenght(head_env), head_env, cmd[i]);
	}
	//printenv_expor(head_env);
	// lbash_env(head_env);
	// exit(0);
	return (0);
}

// int main(int argc, char *argv[], char  *envp[])
// {
//     char *cmd[30] = {"export", "sala=123"};
//     lbash_export(envp, cmd);
//     printf("------------SUCCESS------\n");
//     return(0);
// }