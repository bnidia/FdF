/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 23:55:44 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/11 23:56:26 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "fdf.h"

/*
gcc -Wall -Werror -Wextra
main.c init_data.c draw.c key_and_mouse_controls.c
-L./libraries/mlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
-L./libraries/libft -lft
*/

extern void	init_data(t_fdf *data, char *file_name);
extern void	draw(t_fdf *data);
extern void	key_and_mouse_controls(t_fdf *data);

int	main(int argc, char **argv)
{
	t_fdf	data;

	if (argc != 2)
	{
		errno = EINVAL;
		perror("Error");
		return (1);
	}
	data.shift_x = 1920 / 2;
	data.shift_y = 1080 / 2;
	data.angle_x = 45;
	data.angle_y = 45;
	data.angle_z = 0;
	init_data(&data, argv[1]);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "FDF");
	data.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, \
						&data.bpp, &data.line_len, &data.endian);
	key_and_mouse_controls(&data);
	draw(&data);
	mlx_loop(data.mlx_ptr);
}

void	print_menu(t_fdf *data)
{
	char	*menu;

	mlx_set_font(data->mlx_ptr, data->win_ptr, \
	"*-*-*-*-*-*-*-230-*-*-*-*-iso8859-*");
	menu = "up, down, left, right: move picture";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 40, 0xb8a900, menu);
	menu = "4/6 and 2/8; rotate";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 80, 0xb8a900, menu);
	menu = "+/-: zoom";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 120, 0xb8a900, menu);
	menu = "page up/down: z-scale";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 160, 0xb8a900, menu);
	menu = "0: parallel projections";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 200, 0xb8a900, menu);
}
