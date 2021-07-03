/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:28:12 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/03 11:29:03 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (dst == 0 || src == 0)
		return (0);
	while (src[i] != '\0')
		i++;
	while (src[j] != '\0' && j < dstsize - 1 && dstsize != 0)
	{
		dst[j] = src[j];
		j++;
	}
	if (dstsize > 0)
		dst[j] = '\0';
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == 0)
		return (0);
	i = 0;
	while (i < (int)ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < (int)ft_strlen(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char				*a;
	unsigned int		i;

	a = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (a == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
