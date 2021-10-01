/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:11:20 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/10/01 19:11:23 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_child(char *flag)
{
	static int	is_child;

	if (flag != NULL)
	{
		is_child = 0;
		if (*flag == '1')
			is_child = 1;
	}
	return (is_child);
}

void	signal_from_parent(int sig)
{
	char	*line_buffer;

	if (sig == SIGINT)
	{
		line_buffer = ft_strdup_(rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		write(2, line_buffer, ft_strlen(line_buffer));
		write(2, "  \b\b\nAnasHamid$ ", 16);
		g_exit_s = 1;
		free(line_buffer);
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b", 4);
	}
}

void	signal_from_child(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}

void	sig_handler(int sig)
{
	if (is_child(NULL) == 1)
		signal_from_child(sig);
	else
		signal_from_parent(sig);
}
