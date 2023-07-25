/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:21:44 by luhego            #+#    #+#             */
/*   Updated: 2023/07/25 19:11:35 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_xpm(t_env *env)
{
	int	img_width;
	int	img_height;

		env->mlx_xpm.opened_exit = mlx_xpm_file_to_image(env->mlx, \
		"./xpm/opened_exit.xpm", &img_width, &img_height);
		env->mlx_xpm.closed_exit = mlx_xpm_file_to_image(env->mlx, \
		"./xpm/closed_exit.xpm", &img_width, &img_height);
		env->mlx_xpm.player = mlx_xpm_file_to_image(env->mlx, \
		"./xpm/player.xpm", &img_width, &img_height);
		env->mlx_xpm.wall = mlx_xpm_file_to_image(env->mlx, \
		"./xpm/wall.xpm", &img_width, &img_height);
		env->mlx_xpm.floor = mlx_xpm_file_to_image(env->mlx, \
		"./xpm/floor.xpm", &img_width, &img_height);
		env->mlx_xpm.item = mlx_xpm_file_to_image(env->mlx, \
		"./xpm/item.xpm", &img_width, &img_height);
}

void	ft_fd_size(int fd, int *fd_size)
{
	size_t	column_next;
	size_t	column;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		column = ft_strlen(line);
		if (line[column - 1] == '\n')
			column--;
		*fd_size += 1;
		free(line);
		line = get_next_line(fd);
		column_next = ft_strlen(line);
		if (line && column_next)
		{
			if (line[column_next - 1] == '\n')
				column_next--;
		}
		if (column_next != column && column_next != 0)
			ft_exit("Error\nWrong map.\n", 0);
	}
	free(line);
}

int	ft_valid_file(char *file, int *fd_size, char ***map)
{
	size_t	file_type;
	int		fd;

	file_type = ft_strlen(file) - 4;
	if (ft_strncmp(&file[file_type], ".ber", 4) != 0)
		ft_exit("Error\nWrong file_type.\n", 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	*fd_size = 0;
	ft_fd_size(fd, fd_size);
	*map = malloc(sizeof(char *) * (*fd_size + 1));
	if (!*map)
		ft_exit("Error\nMissing memory", 0);
	close (fd);
	return (1);
}

int	ft_fill_map(int *fd_size, char *file, char **map)
{
	int	fd;
	int	x;
	int	y;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	x = 0;
	while (x != *fd_size)
	{
		map[x] = get_next_line(fd);
		y = ft_strlen(map[x]) - 1;
		if (map[x][y] == '\n')
			map[x][y] = 0;
		x++;
	}
	map[x] = 0;
	close (fd);
	return (1);
}
