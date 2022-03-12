/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:45:58 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/11 12:47:16 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

extern void		print_menu(t_fdf *data);
static void		bresenham(t_line line, t_fdf *data);
static void		my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
static void		zoom_rotate_shift(t_fdf *data, double *x, double *y, double z);

void	draw(t_fdf *data)
{
	t_line	line;

	line.y1 = -1;
	while (++line.y1 < data->height)
	{
		line.x1 = -1;
		while (++line.x1 < data->width)
		{
			if (line.x1 < data->width - 1)
			{
				line.x2 = line.x1 + 1;
				line.y2 = line.y1;
				bresenham(line, data);
			}
			if (line.y1 < data->height - 1)
			{
				line.x2 = line.x1;
				line.y2 = line.y1 + 1;
				bresenham(line, data);
			}
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	print_menu(data);
}

void	redraw_image(t_fdf *data)
{
	int		i;
	char	*dst;

	i = 0;
	while (i <= 1080 * (data->line_len + 1))
	{
		dst = data->addr + i;
		*(unsigned int *) dst = 0;
		i++;
	}
	draw(data);
}

static void	bresenham(t_line line, t_fdf *data)
{
	double	x_step;
	double	y_step;
	double	z1;
	double	z2;

	z1 = data->z_matrix[(int)line.y1][(int)line.x1] * data->lift;
	z2 = data->z_matrix[(int)line.y2][(int)line.x2] * data->lift;
	if (z1 || z2)
		data->color = 0xe80c0c;
	else
		data->color = 0xffffff;
	zoom_rotate_shift(data, &line.x1, &line.y1, z1);
	zoom_rotate_shift(data, &line.x2, &line.y2, z2);
	x_step = line.x2 - line.x1;
	y_step = line.y2 - line.y1;
	data->max = ft_max_double(ft_abs_d(x_step), ft_abs_d(y_step));
	x_step /= data->max;
	y_step /= data->max;
	while ((int)(line.x1 - line.x2) || (int)(line.y1 - line.y2))
	{
		my_mlx_pixel_put(data, (int)line.x1, (int)line.y1, data->color);
		line.x1 += x_step;
		line.y1 += y_step;
	}
}

static void	zoom_rotate_shift(t_fdf *data, double *x, double *y, double z)
{
	double	angle_in_radians;

	*x = (*x - data->width / 2) * data->zoom;
	*y = (*y - data->height / 2) * data->zoom;
	angle_in_radians = data->angle_x * (M_PI / 180.0);
	*y = *y * cos(angle_in_radians) - z * sin(angle_in_radians);
	z = *y * sin(angle_in_radians) + z * cos(angle_in_radians);
	angle_in_radians = data->angle_y * (M_PI / 180.0);
	*x = *x * cos(angle_in_radians) + z * sin(angle_in_radians);
	angle_in_radians = data->angle_z * (M_PI / 180.0);
	*x = *x * cos(angle_in_radians) - *y * sin(angle_in_radians);
	*y = *x * sin(angle_in_radians) + *y * cos(angle_in_radians);
	*x += data->shift_x;
	*y += data->shift_y;
}

static void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x < 1920 && y < 1080 && x > 0 && y > 0)
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *) dst = color;
	}
}
