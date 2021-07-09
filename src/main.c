/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:14:48 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/09 16:56:50 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	letter_count(t_map *map, char letter)
{
	int	i;
	int	j;
	int	rst;

	i = 0;
	rst = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == letter)
				rst++;
			j++;
		}
		i++;
	}
	return (rst);
}

void	msg_end(char *err_msg, int case_num, t_data *data)
{
	char	*tmp;

	if (case_num < 1)
	{
		tmp = ft_strjoin("Error\n", err_msg);
		write(2, tmp, ft_strlen(tmp));
		free(tmp);
	}
	else
		write(1, err_msg, ft_strlen(err_msg));
	if (data->map.map != 0)
		allo_free(data->map.map);
	if (data->win != 0)
		mlx_destroy_window(data->mlx, data->win);
	if (data->imgs.back.img != 0)
		mlx_destroy_image(data->mlx, data->imgs.back.img);
	if (data->imgs.wall.img != 0)
		mlx_destroy_image(data->mlx, data->imgs.wall.img);
	if (data->imgs.item.img != 0)
		mlx_destroy_image(data->mlx, data->imgs.item.img);
	if (data->imgs.exit.img != 0)
		mlx_destroy_image(data->mlx, data->imgs.exit.img);
	if (data->imgs.player.img != 0)
		mlx_destroy_image(data->mlx, data->imgs.player.img);
	exit (0);
}

int	press_X(t_data *data)
{
	msg_end("X_BUTTON END\n", 1, data);
	return (0);
}

int	check_element(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
					&& map->map[i][j] != 'P' && map->map[i][j] != 'C'
					&& map->map[i][j] != 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2 && ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber") == 0)
	{
		init_data(&data);
		if (parse_map(&data.map, argv[1]) == 0)
			msg_end("can't read the file\n", 0, &data);
		if (check_map(&data.map) == 0)
			msg_end("map check fail\n", 0, &data);
		save_imgs(&data);
		screen(&data);
	}
	else
		write(1, "Error\ninvalid file\n", 19);
	return (0);
}
