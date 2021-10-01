/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:06:45 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 14:09:23 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

t_node	*linked_list(t_node *head, char **env)
{
	int		i;
	int		a;

	i = -1;
	a = 1;
	while (env[++i] != NULL)
	{
		head = insert(a, env[i], head);
		++a;
	}
	return (head);
}

int	lenght(t_node *current)
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
	return (lenght);
}

int	correct_var(const char *var)
{
	int		i;

	if (ft_isdigit(var[0]))
		return (0);
	i = 0;
	while (var[i])
		if (!ft_isalnum(var[i++]))
			return (0);
	return (1);
}

void	sort_env(t_node	*head, int i, int j, int count)
{
	char	*temp;
	t_node	*current;
	t_node	*next;

	while (++i < count - 1)
	{
		current = head;
		next = head->next;
		j = i;
		while (++j < count)
		{
			if (ft_strcmp (current->data, next->data) > 0)
			{
				temp = ft_strdup(current->data);
				free(current->data);
				current->data = ft_strdup(next->data);
				free(next->data);
				next->data = ft_strdup(temp);
				free(temp);
			}
			current = current->next;
			next = next->next;
		}
	}
}

int	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (-1);
}
