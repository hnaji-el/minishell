/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:45:14 by ael-kass          #+#    #+#             */
/*   Updated: 2021/10/01 12:58:40 by ael-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int	check_n(char **args)
{
	int		i;

	i = 0;
	if (ft_strcmp (*args, "-n") == 0)
	{
		args++;
		while (ft_strcmp(*args, "-n") == 0)
			args++;
		i = 2;
		while (*args != NULL)
		{
			ft_putstr_fd(*args, STDOUT_FILENO);
			if (*(args + 1))
				write(1, " ", 1);
			args++;
		}
		return (1);
	}
	return (0);
}

int	lbash_echo(char **cmd)
{
	if (cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	cmd++;
	if (!check_n (cmd))
	{
		while (*cmd != NULL)
		{
			ft_putstr_fd(*cmd, 1);
			cmd++;
			if (*cmd != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (0);
}
