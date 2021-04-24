/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:48:53 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/02/06 08:57:30 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	nb;
	int		sign;

	sign = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' && *(str + 1) == '-')
		return (0);
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (nb < 0)
		return ((sign > 0) ? -1 : 0);
	return (sign * nb);
}
