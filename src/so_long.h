/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:32:43 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/03 16:20:21 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		screen_width;
	int		screen_height;
}	t_map;

typedef struct s_imgs
{
	t_image back;
	t_image	wall;
	t_image	item;
	t_image	exit;
	t_image	player;
}	t_imgs;

int		cnt_word(char const *s, char c);
char	**allo_free(char **rst);
char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);

#endif
