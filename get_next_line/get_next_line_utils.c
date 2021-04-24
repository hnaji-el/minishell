/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 02:17:21 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/04/24 15:24:05 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	dst = (char *)malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		dst[i] = s[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*total;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (total == NULL)
		return (NULL);
	ptr = total;
	while (*s1 != '\0')
	{
		*total = *s1;
		total++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*total = *s2;
		total++;
		s2++;
	}
	*total = '\0';
	return (ptr);
}

size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
{
	char		*dst;
	size_t		i;

	i = 0;
	dst = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
