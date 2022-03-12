/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:51:56 by bnidia            #+#    #+#             */
/*   Updated: 2022/03/11 12:51:57 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

static void	get_dimensions(t_fdf *data, char *file_name);
static int	count_width(const char *line);
static void	fill_matrix(int *z_line, char *line);
int			ft_close(t_fdf *data);

void	init_data(t_fdf *data, char *file_name)
{
	data->zoom = 20;
	data->lift = 1;
	get_dimensions(data, file_name);
	data->fd = open(file_name, O_RDONLY, 0);
	if (data->fd == -1)
		exit (3);
	data->z_matrix = (int **)malloc(sizeof(int *) * ((int)data->height + 1));
	if (data->z_matrix == NULL)
		exit (4);
	data->i = 0;
	while (42)
	{
		data->line = get_next_line(data->fd);
		if (data->line == NULL)
			break ;
		data->z_matrix[data->i] = \
						(int *)malloc(sizeof(int) * ((int)data->width + 1));
		if (data->z_matrix[data->i] == NULL)
			ft_close(data);
		fill_matrix(data->z_matrix[data->i++], data->line);
		free(data->line);
	}
	close(data->fd);
	data->z_matrix[data->i] = NULL;
}

static void	get_dimensions(t_fdf *data, char *file_name)
{
	char	*line;
	char	*temp;

	data->height = 0;
	data->width = 1;
	data->fd = open(file_name, O_RDONLY, 0);
	if (data->fd == -1)
		perror ("Error");
	if (data->fd == -1)
		exit (1);
	temp = get_next_line(data->fd);
	line = ft_strtrim(temp, " \n");
	free(temp);
	if (line == NULL)
		exit (2);
	data->width = count_width(line);
	while (line)
	{
		data->height++;
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
	close (data->fd);
}

static int	count_width(const char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			counter++;
		while (line[i] == ' ' && line[i + 1] == ' ')
			i++;
		i++;
	}
	return (counter);
}

static void	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i] != NULL)
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

int	ft_close(t_fdf *data)
{
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	while (data->height >= 0)
		free(data->z_matrix[(int)data->height--]);
	free(data->z_matrix);
	exit(0);
}
