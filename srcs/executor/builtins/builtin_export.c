/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 08:00:48 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 13:29:38 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int	add_var(int n, t_node *head, char *cmd)
{
	t_node	*current;
	char	**dst;

	if (n == 0)
		n = 1;
	current = head;
	dst = ft_split(cmd, '=');
	if (!correct_var(dst[0]))
	{
		free_array(dst);
		return (print_error(dst[0], ": export : not a valid is_identifier", 1));
	}
	current = find(dst[0], current);
	if (current == NULL)
		insert(n, cmd, head);
	else
	{
		free(current->data);
		current->data = ft_strdup(cmd);
	}
	free_array(dst);
	return (0);
}

void	printenv_expor(t_node *head, int out_fd, char *str, int count)
{
	char	**dst;
	t_node	*current;

	current = head;
	count = lenght(current);
	sort_env(current, -1, 0, count);
	while (current != NULL)
	{
		str = ft_strchr(current->data, '=');
		if (str)
			str = str + 1;
		dst = ft_split(current->data, '=');
		ft_putstr_fd("declare -x ", out_fd);
		ft_putstr_fd(dst[0], out_fd);
		if (str)
		{
			write(out_fd, "=\"", 2);
			ft_putstr_fd(str, out_fd);
			write(out_fd, "\"", 1);
		}
		write(out_fd, "\n", 1);
		current = current->next;
		free_array(dst);
	}
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
		return (head);
	}
	temp1 = head;
	i = -1;
	while (temp1->next != NULL)
		temp1 = temp1->next;
	temp1->next = temp;
	return (head);
}

t_node	*find(char *str, t_node *head)
{
	t_node	*current;
	char	**dst;

	current = head;
	if (current == NULL)
		return (NULL);
	dst = ft_split((current)->data, '=');
	while (ft_strcmp (dst[0], str) != 0)
	{
		if (current->next == NULL)
		{
			free_array(dst);
			return (NULL);
		}
		else
		{
			current = current->next;
			free_array(dst);
			dst = ft_split(current->data, '=');
		}
	}
	free_array(dst);
	return (current);
}

int	lbash_export(t_node	*head_env, char **cmd, int out_fd)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (cmd[1] == NULL)
		printenv_expor(head_env, out_fd, NULL, 0);
	while (cmd[++i] != NULL)
		ret = add_var(lenght(head_env), head_env, cmd[i]);
	return (ret);
}
