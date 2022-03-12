/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:47:51 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/11 12:51:35 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_fdf
{
	double	width;
	double	height;
	int		**z_matrix;
	double	zoom;
	int		color;
	int		shift_x;
	int		shift_y;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	char	*line;
	double	lift;
	int		fd;
	int		i;
	double	max;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;

}				t_fdf;

typedef struct s_line
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
}				t_line;

#endif