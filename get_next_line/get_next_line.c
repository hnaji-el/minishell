/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 02:14:17 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/04/24 15:26:53 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		eof_neof(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	myfree(char **fr)
{
	if (*fr != NULL)
	{
		free(*fr);
		*fr = NULL;
	}
}

int		ft_len(char *str, int len)
{
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len);
}

int		read_join(char **str, int fd)
{
	int		r;
	char	*buffer;
	char	*fr;

	r = 1;
	if ((buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (-1);
	if (!eof_neof(*str))
	{
		while (r > 0)
		{
			if ((r = read(fd, buffer, BUFFER_SIZE)) == -1)
				return (-1);
			buffer[r] = '\0';
			fr = *str;
			if ((*str = ft_strjoin(*str, buffer)) == NULL)
				return (-1);
			myfree(&fr);
			if (eof_neof(*str))
				break ;
		}
	}
	myfree(&buffer);
	return (r);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	char		*fr;
	int			r;
	int			len;

	if (BUFFER_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	if (str == NULL)
	{
		if ((str = ft_strdup("")) == NULL)
			return (-1);
	}
	if ((r = read_join(&str, fd)) == -1)
		return (-1);
	len = ft_len(str, 0);
	if ((*line = ft_substr(str, 0, len)) == NULL)
		return (-1);
	fr = str;
	str = (r == 0) ? NULL : ft_strdup(str + len + 1);
	if ((r != 0) && str == NULL)
		return (-1);
	myfree(&fr);
	return (r == 0 ? 0 : 1);
}
