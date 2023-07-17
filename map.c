/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:21:44 by luhego            #+#    #+#             */
/*   Updated: 2023/07/17 17:34:17 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fd_size(int fd)
{
	size_t  columnNext;
	size_t  column;
	int		count;
	char    *line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		column = ft_strlen(line);
		if (line[column - 1] == '\n')
			column--;
		count++;
		free(line);
		if ((line = get_next_line(fd)) && (columnNext = ft_strlen(line)))
		{
			if (line[columnNext - 1] == '\n')
				columnNext--;
		}
		if (columnNext != column)
			ft_exit("Error\nWrong map.\n", 0, 0);
	}
	free(line);
	return (count);
}

int ft_valid_file(char *file, int *fd_size, char ***map)
{
	size_t  file_type;
	int     fd;

	file_type = ft_strlen(file) - 4;
	if (ft_strncmp(&file[file_type], ".ber", 4) != 0)
		ft_exit("Error\nWrong file_type.\n", 0, 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	*fd_size = ft_fd_size(fd);
	printf("fd_size = %i\n", *fd_size);
	*map = malloc(sizeof(char *) * (*fd_size + 1));
	if (!*map)
		ft_exit(0, "malloc", 0);
	close (fd);
	return (1);
}

int ft_fill_map(int *fd_size, char *file, char **map)
{
	int fd;
	int x;
	int y;

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
