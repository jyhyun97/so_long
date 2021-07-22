/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:36:16 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/09 15:25:07 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_W(t_data *data, int p_x, int p_y)
{
	char	tmp;

	tmp = data->map.map[p_y - 1][p_x];
	if (tmp == 'E')
	{
		if (letter_count(&data->map, 'C') == 0)
		{
			print_count(data);
			msg_end("Game clear~!\n", 1, data);
		}
	}
	else
	{
		if (tmp == 'C')
			tmp = '0';
		data->map.map[p_y - 1][p_x] = 'P';
		data->map.map[p_y][p_x] = tmp;
		print_count(data);
	}
}

static void	move_A(t_data *data, int p_x, int p_y)
{
	char	tmp;

	tmp = data->map.map[p_y][p_x - 1];
	if (tmp == 'E')
	{
		if (letter_count(&data->map, 'C') == 0)
		{
			print_count(data);
			msg_end("Game clear~!\n", 1, data);
		}
	}
	else
	{
		if (tmp == 'C')
			tmp = '0';
		data->map.map[p_y][p_x - 1] = 'P';
		data->map.map[p_y][p_x] = tmp;
		print_count(data);
	}
}

static void	move_S(t_data *data, int p_x, int p_y)
{
	char	tmp;

	tmp = data->map.map[p_y + 1][p_x];
	if (tmp == 'E')
	{
		if (letter_count(&data->map, 'C') == 0)
		{
			print_count(data);
			msg_end("game clear~!\n", 1, data);
		}
	}
	else
	{
		if (tmp == 'C')
			tmp = '0';
		data->map.map[p_y + 1][p_x] = 'P';
		data->map.map[p_y][p_x] = tmp;
		print_count(data);
	}
}

static void	move_D(t_data *data, int p_x, int p_y)
{
	char	tmp;

	tmp = data->map.map[p_y][p_x + 1];
	if (tmp == 'E')
	{
		if (letter_count(&data->map, 'C') == 0)
		{
			print_count(data);
			msg_end("game clear~!\n", 1, data);
		}
	}
	else
	{
		if (tmp == 'C')
			tmp = '0';
		data->map.map[p_y][p_x + 1] = 'P';
		data->map.map[p_y][p_x] = tmp;
		print_count(data);
	}
}

int	movement(int keycode, t_data *data)
{
	int		p_x;
	int		p_y;

	if (keycode == KEY_ESC)
		msg_end("ESC_press_end\n", 1, data);
	p_y = -1;
	while (++p_y < data->map.height && data->map.map[p_y][p_x] != 'P')
	{
		p_x = 0;
		while (p_x < data->map.width && data->map.map[p_y][p_x] != 'P')
			p_x++;
		if (data->map.map[p_y][p_x] == 'P')
			break ;
	}
	if (keycode == KEY_W && data->map.map[p_y - 1][p_x] != '1')
		move_W(data, p_x, p_y);
	if (keycode == KEY_A && data->map.map[p_y][p_x - 1] != '1')
		move_A(data, p_x, p_y);
	if (keycode == KEY_S && data->map.map[p_y + 1][p_x] != '1')
		move_S(data, p_x, p_y);
	if (keycode == KEY_D && data->map.map[p_y][p_x + 1] != '1')
		move_D(data, p_x, p_y);
	return (1);
}
