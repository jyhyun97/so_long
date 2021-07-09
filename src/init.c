/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:46:58 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/09 16:55:31 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = 0;
	data->map.map = 0;
	data->imgs.back.img = 0;
	data->imgs.item.img = 0;
	data->imgs.wall.img = 0;
	data->imgs.player.img = 0;
	data->imgs.exit.img = 0;
}

int	parse_map(t_map *map, char *argv)
{
	int		fd;
	char	buf[2];
	char	*rst;
	char	*tmp;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	rst = ft_strdup("");
	while (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		tmp = ft_strjoin(rst, buf);
		free(rst);
		rst = tmp;
	}
	map->map = ft_split(rst, '\n');
	map->width = ft_strlen(map->map[0]);
	map->height = cnt_word(rst, '\n');
	free(rst);
	map->screen_width = 1600;
	map->screen_height = 900;
	return (1);
}

int	check_map(t_map *map)
{
	int	i;

	if (map->height * 32 * map->width * 32
		> map->screen_height * map->screen_width)
		return (0);
	if (map->height < 3 && map->width < 3 && map->height * map->width < 15)
		return (0);
	if (letter_count(map, 'E') != 1 || letter_count(map, 'P') != 1
		|| letter_count(map, 'C') < 1 || check_element(map) == 0)
		return (0);
	i = -1;
	while (map->map[0][++i] != '\0')
	{
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			return (0);
	}
	i = -1;
	while (map->map[++i] != 0)
	{
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1'
			|| ((int)ft_strlen(map->map[i]) != map->width))
			return (0);
	}
	return (1);
}

static void	imgs_addr(t_imgs *imgs)
{
	imgs->back.addr = mlx_get_data_addr(imgs->back.img, &imgs->back.bpp,
			&imgs->back.line_length, &imgs->back.endian);
	imgs->wall.addr = mlx_get_data_addr(imgs->wall.img, &imgs->wall.bpp,
			&imgs->back.line_length, &imgs->back.endian);
	imgs->item.addr = mlx_get_data_addr(imgs->item.img, &imgs->item.bpp,
			&imgs->item.line_length, &imgs->item.endian);
	imgs->exit.addr = mlx_get_data_addr(imgs->exit.img, &imgs->exit.bpp,
			&imgs->exit.line_length, &imgs->exit.endian);
	imgs->player.addr = mlx_get_data_addr(imgs->player.img, &imgs->player.bpp,
			&imgs->player.line_length, &imgs->player.endian);
}

void	save_imgs(t_data *data)
{
	int	width;
	int	height;

	data->imgs.back.img = mlx_xpm_file_to_image(data->mlx, "./img/empty.xpm",
			&width, &height);
	data->imgs.wall.img = mlx_xpm_file_to_image(data->mlx, "./img/wall.xpm",
			&width, &height);
	data->imgs.item.img = mlx_xpm_file_to_image(data->mlx, "./img/apple.xpm",
			&width, &height);
	data->imgs.exit.img = mlx_xpm_file_to_image(data->mlx, "./img/ladder.xpm",
			&width, &height);
	data->imgs.player.img = mlx_xpm_file_to_image(data->mlx, "./img/worm.xpm",
			&width, &height);
	if (data->imgs.back.img == 0 || data->imgs.wall.img == 0
		|| data->imgs.item.img == 0 || data->imgs.exit.img == 0
		|| data->imgs.player.img == 0)
		msg_end("texture error\n", 0, data);
	imgs_addr(&data->imgs);
}
