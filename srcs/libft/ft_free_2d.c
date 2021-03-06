/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 17:28:59 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/02/08 15:38:52 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char ***str)
{
	int		j;

	j = 0;
	if (*str != NULL)
		j = ft_strlen_2d(*str);
	while (j > 0)
	{
		j--;
		free(str[0][j]);
	}
	free(*str);
	*str = NULL;
}
