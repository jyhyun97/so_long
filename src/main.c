/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:14:48 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/07/03 17:14:26 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"

void	mlx_pixel_put_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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
/*
int	check_map(t_map *map)
{
	//맵 규칙 체크해서 하나라도 틀리면 0, 다 통과하면 1 반환
	//1. 직사각형일 것(모든 행의 길이가 같을 것)
	//2. 가로 세로 32 곱한 게 화면 사이즈 오버하지 않을 것 : 화면 크기는 어떻게 할까요? mlx_get_screen_size(mlx, &map->width, &map->height); 아 근데 이건 parse img 시점에서 해야 하고, opengl에선 못씀..
	//3. 벽은 1로 둘러싸여 있을 것
	//4. 필수 요소 3개가 존재할 것, e, p는 딱 1개, c는 몇 개라도 괜찮음
	//5. 최소 가로 * 세로 15 이상이고 각각 3 이상일 것 내가 정한 규칙이긴 한데..
}
*/

void fill_background(t_image *back, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->screen_width)
	{
		j = 0;
		while (j < map->screen_height)
		{
			mlx_pixel_put_img(back, i, j, 0x0000bdc5);
			j++;
		}
		i++;
	}
}

int parse_imgs(t_imgs *imgs, t_map *map, void *mlx)
{
	int width;
	int	height;

	imgs->back.img = mlx_new_image(mlx, map->screen_width, map->screen_height);
	imgs->back.addr = mlx_get_data_addr(imgs->back.img, &imgs->back.bpp,
		&imgs->back.line_length, &imgs->back.endian);
	fill_background(&imgs->back, map);
	imgs->wall.img = mlx_xpm_file_to_image(mlx, "./img/wall.xpm", &width, &height);
	imgs->wall.addr = mlx_get_data_addr(imgs->wall.img, &imgs->wall.bpp,
		&imgs->back.line_length, &imgs->back.endian);
	imgs->item.img = mlx_xpm_file_to_image(mlx, "./img/apple.xpm", &width, &height); 
	imgs->item.addr = mlx_get_data_addr(imgs->item.img, &imgs->item.bpp,
		&imgs->item.line_length, &imgs->item.endian);
	imgs->exit.img = mlx_xpm_file_to_image(mlx, "./img/ladder.xpm", &width, &height); 
	imgs->exit.addr = mlx_get_data_addr(imgs->exit.img, &imgs->exit.bpp,
		&imgs->exit.line_length, &imgs->exit.endian);
	imgs->player.img = mlx_xpm_file_to_image(mlx, "./img/worm.xpm", &width, &height); 
	imgs->player.addr = mlx_get_data_addr(imgs->player.img, &imgs->player.bpp,
		&imgs->player.line_length, &imgs->player.endian);
	return (1);
}


void get_image(void *mlx, void *win, t_imgs *imgs, t_map *map)
{
	int i = 0;
	int j = 0;

	mlx_put_image_to_window(mlx, win, imgs->back.img, 0, 0);
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			if (map->map[j][i] == '1')
				mlx_put_image_to_window(mlx, win, imgs->wall.img, i * 32, j * 32);
			else if (map->map[j][i] == 'P')
				mlx_put_image_to_window(mlx, win, imgs->player.img, i * 32, j * 32);
			else if (map->map[j][i] == 'C')
				mlx_put_image_to_window(mlx, win, imgs->item.img, i * 32, j * 32);
			else if (map->map[j][i] == 'E')
				mlx_put_image_to_window(mlx, win, imgs->exit.img, i * 32, j * 32);
			j++;
		}
		i++;
	}
}

void screen(t_map *map, t_imgs *imgs)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	//mlx_get_screen_size(mlx, &map->screen_width, &map->screen_height);
	//check_map(map, mlx) //0이면 map free 후 에러 메세지, exit
	parse_imgs(imgs, map, mlx); //실패하면 map free, image destroy 후 에러메세지, exit
	win = mlx_new_window(mlx, map->width * 32, map->height * 32, "so_long");
	get_image(mlx, win, imgs, map);//mlx put image to window
	mlx_loop(mlx);
	//mlx_key_hook//이동에 따라 map.map 변경해주고 그에 맞춰 이미지 재출력 get_image 하기
	//esc, x버튼 경우 잘 free하고 exit
}

int	main(int argc, char *argv[])
{
	t_map	map;//free : map.map allo_free 쓰면 됨
	t_imgs	imgs;//free : mlx_image_destroy함수로 4개 다 free

	if (argc == 2 && ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber") == 0)
	{
		parse_map(&map, argv[1]); //0이면 파일 오픈 실패, exit
		screen(&map, &imgs); //화면에 띄우기, mlx hook으로 방향키 조작... 여기까지 오면 딱히 문제될 요소는 없을 듯
	}
	else
		printf("invalid file\n");
	return (0);
}
