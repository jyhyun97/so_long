/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:32:43 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/09 16:53:46 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define KEY_PRESS 2
# define BUTTON_X 17
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../mlx/mlx.h"

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
	t_image	back;
	t_image	wall;
	t_image	item;
	t_image	exit;
	t_image	player;
}	t_imgs;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int	count;
	t_map	map;
	t_imgs	imgs;
}	t_data;

int		cnt_word(char const *s, char c);
char	**allo_free(char **rst);
char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);

char	*ft_itoa(int n);

void	init_data(t_data *data);
int		parse_map(t_map *map, char *argv);
int		check_map(t_map *map);
void	save_imgs(t_data *data);

int		movement(int keycode, t_data *data);

int		letter_count(t_map *map, char letter);
void	msg_end(char *err_msg, int case_num, t_data *data);
int		press_X(t_data *data);
int		check_element(t_map *map);

void	mlx_pixel_put_img(t_image *img, int x, int y, int color);
int		get_image(t_data *data);
void	screen(t_data *data);

#endif
