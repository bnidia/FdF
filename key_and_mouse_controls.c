/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_controls.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:11:59 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/11 13:12:00 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/* all keys are under Ubuntu 20.04.4 LTS */
#define KEY_ESC 65307
#define KEY_PG_UP 65365
#define KEY_PG_DOWN 65366
#define KEY_0 65438
#define KEY_PLUS 65451
#define KEY_MINUS 65453
#define KEY_ROT_SLASH 65455
#define KEY_ROT_ASTERISK 65450
#define KEY_ROT_8 65431
#define KEY_ROT_2 65433
#define KEY_ROT_4 65430
#define KEY_ROT_6 65432
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

extern int	ft_close(t_fdf *data);
static int	deal_key(int key, t_fdf *data);
extern void	draw(t_fdf *data);
extern void	redraw_image(t_fdf *data);
static void	parallel_projection(t_fdf *data);
static void	rotation_keys(t_fdf *data, int key);
static void	rotation_angle_set(double *angle, char operation);

void	key_and_mouse_controls(t_fdf *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, deal_key, data);
	mlx_hook(data->win_ptr, 17, 0, ft_close, data);
}

static int	deal_key(int key, t_fdf *data)
{
	rotation_keys(data, key);
	if (key == KEY_UP)
		data->shift_y -= 10;
	else if (key == KEY_DOWN)
		data->shift_y += 10;
	else if (key == KEY_LEFT)
		data->shift_x -= 10;
	else if (key == KEY_RIGHT)
		data->shift_x += 10;
	else if (key == KEY_PLUS)
		data->zoom *= 1.1;
	else if (key == KEY_MINUS)
		data->zoom *= 0.9;
	else if (key == KEY_PG_UP)
		data->lift *= 1.1f;
	else if (key == KEY_PG_DOWN)
		data->lift *= 0.9f;
	else if (key == KEY_ESC)
		ft_close(data);
	else if (key == KEY_0)
		parallel_projection(data);
	else
		return (0);
	redraw_image(data);
	return (0);
}

static void	parallel_projection(t_fdf *data)
{
	static int	set = 0;

	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	if (set == 1)
		data->angle_x = 90;
	if (set == 2)
		data->angle_y = 90;
	if (set++ == 3)
	{
		data->angle_x = 45;
		data->angle_y = 45;
		set = 0;
	}
}

static void	rotation_keys(t_fdf *data, int key)
{
	if (key == KEY_ROT_8)
		rotation_angle_set(&data->angle_x, '+');
	else if (key == KEY_ROT_2)
		rotation_angle_set(&data->angle_x, '-');
	else if (key == KEY_ROT_4)
		rotation_angle_set(&data->angle_y, '+');
	else if (key == KEY_ROT_6)
		rotation_angle_set(&data->angle_y, '-');
	else if (key == KEY_ROT_ASTERISK)
		rotation_angle_set(&data->angle_z, '+');
	else if (key == KEY_ROT_SLASH)
		rotation_angle_set(&data->angle_z, '-');
	else
		return ;
	redraw_image(data);
}

static void	rotation_angle_set(double *angle, char operation)
{
	if (operation == '+')
		*angle += 5;
	if (operation == '-')
		*angle -= 5;
	if (*angle > 360)
		*angle -= 360;
	if (*angle < 0)
		*angle += 360;
}
