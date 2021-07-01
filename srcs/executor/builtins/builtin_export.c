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

	sort_env(head);
    while (head != NULL)
    {
       dst = ft_split(head->data, '=');
       ft_putstr_fd("declare -x ", 1);
       ft_putstr_fd(dst[0], 1);
       write(1, "=\"", 2);
       ft_putstr_fd(dst[1], 1);
       write(1, "\"\n", 2);
	   head = head->next;
    }
}

void	add_var(int n, t_node **head, char *cmd)
{
	t_node *current;
	char	**dst;
	
	dst = ft_split(cmd, '=');

	current = find(dst[0], *head);
	//printf("CURRENT : %s\n", current->data);
	if (current == NULL)
		*head = insert(n, cmd, *head);
	else
		(*head)->data = cmd;
	//printf("data : %s\n",current->data);
	
}

t_node	*insert(int n, char *data, t_node *head)
{
	
	t_node	*temp;
	t_node	*temp1;
	int		i;

	temp = malloc(sizeof(t_node));
	temp->data = data;
	temp->next = NULL;
	if (n == 1)
	{
		temp->next = head;
		head = temp;
		return head;
	}
	temp1 = head;
	i = -1;
	while(++i < n - 2)
	{
		temp1 = temp1->next;
	}
	temp->next = temp1->next;
	temp1->next = temp;
	return head;
}

t_node	*find(char *str, t_node *head)
{
	//start from the first link
	t_node	*current = head;
	char **dst;

	//if list is empty
	if(head == NULL)
		return NULL;
	//navigate through list
	dst = ft_split(current->data, '=');
	while(ft_strcmp(dst[0], str))
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

t_node    *lbash_export(char *envp[], char **cmd)
{
	int	i;
	int	a;
	t_node*		head;
	head = NULL;
	i = -1;
	a = 1;
	while (envp[++i] != NULL)
	{
		head = insert(a, envp[i], head);
		a++;
	}
	i = 0;
	if (cmd[1] == NULL)
		printenv_expor(head);	
	while (cmd[++i] != NULL)
	{
		add_var(a, &head, cmd[i]);
		a++;
	}
	return (head);
}

// int main(int argc, char *argv[], char  *envp[])
// {
//     char *cmd[30] = {"export", "salam=12"};
//     lbash_export(envp, cmd);
//     printf("------------SUCCESS------\n");
//     return(0);
// }