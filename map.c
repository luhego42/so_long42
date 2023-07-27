/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:21:44 by luhego            #+#    #+#             */
/*   Updated: 2023/07/27 23:00:18 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		ft_exit("Error\nMissing memory.\n", 0);
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

int	ft_xpm_exist(void)
{
	int	fd;

	fd = open("xpm/closed_exit.xpm", O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open("xpm/opened_exit.xpm", O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open("xpm/floor.xpm", O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open("xpm/item.xpm", O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open("xpm/player.xpm", O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open("xpm/wall.xpm", O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (1);
}
