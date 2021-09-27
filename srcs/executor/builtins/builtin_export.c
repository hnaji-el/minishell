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

	if (current == NULL)
		return (-1);
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
	char *str;

	current = find("_", head);
	lbash_unset(head, &current->data);
	free(current->data);
	current = head;
	sort_env(current);
    while (current != NULL)
    {
       str = ft_strchr(current->data, '=');
	   if (str)
			str = str + 1;
	   dst = ft_split(current->data, '=');
       ft_putstr_fd("declare -x ", 1);
       ft_putstr_fd(dst[0], 1);
	   if (str)
	   {
	   		write(1, "=\"", 2);
       		ft_putstr_fd(str, 1);
       		write(1, "\"", 1);
	   }
	   write(1, "\n", 1);
	   current = current->next;
    }
}

int		correct_var(const char *var)
{
	int		i;

	if (ft_isdigit(var[0]))
		return(0);
	i = 0;
	while (var[i])
		if (!ft_isalnum(var[i++]))
			return (0);
	return (1);
}

int		add_var(int n, t_node *head, char *cmd)
{
	t_node *current;
	char	**dst;

	if (n == 0)
		n = 1;
	current = head;
	dst = ft_split(cmd, '=');
	if (!correct_var(dst[0]))
	{
		perror("lbash: not a valid is_identifier");
		return (127);
	}
	current = find(dst[0], current);
	if (current == NULL)
		insert(n, cmd, head);
	else
		current->data = ft_strdup(cmd);
	return (0);
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
	i = 0;
	if (cmd[1] == NULL)
		printenv_expor(head_env);	
	while (cmd[++i] != NULL)
	{
		add_var(lenght(head_env), head_env, cmd[i]);
	}
	return (0);
}