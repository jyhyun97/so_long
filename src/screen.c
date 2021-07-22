/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:33:02 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/22 15:40:19 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_count(t_data *data)
{
	char	*output;

	data->count++;
	output = ft_itoa(data->count);
	write(1, output, ft_strlen(output));
	write(1, "\n", 1);
	free(output);
}

void	mlx_pixel_put_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	fill_background(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.width)
	{
		j = -1;
		while (++j < data->map.height)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->imgs.back.img,
				i * 32, j * 32);
			if (data->map.map[j][i] == 'E')
				mlx_put_image_to_window(data->mlx, data->win,
					data->imgs.exit.img, i * 32, j * 32);
		}
	}
}

int	get_image(t_data *data)
{
	int	i;
	int	j;

	fill_background(data);
	i = -1;
	while (++i < data->map.width)
	{
		j = -1;
		while (++j < data->map.height)
		{
			if (data->map.map[j][i] == '1')
				mlx_put_image_to_window(data->mlx, data->win,
					data->imgs.wall.img, i * 32, j * 32);
			else if (data->map.map[j][i] == 'P')
				mlx_put_image_to_window(data->mlx, data->win,
					data->imgs.player.img, i * 32, j * 32);
			else if (data->map.map[j][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win,
					data->imgs.item.img, i * 32, j * 32);
		}
	}
	return (1);
}

void	screen(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.width * 32,
			data->map.height * 32, "so_long");
	get_image(data);
	mlx_hook(data->win, KEY_PRESS, 0, &movement, data);
	mlx_loop_hook(data->mlx, &get_image, data);
	mlx_hook(data->win, BUTTON_X, 0, &press_X, data);
	mlx_loop(data->mlx);
}
