#include "so_long.h"

static int ft_valid_map(char **map)
{
	int y;
	int x;

	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1'
			&& map[y][x] != 'C' && map[y][x] != 'E' && map[y][x] != 'P')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int ft_map_limit(char **map, int column_max)
{
	int line_max;
	int line;
	int column;

	line_max = ft_strlen(map[0]) - 1;
	column = 0;

	while (map[column])
	{
		line = 0;
		while(map[column][line])
		{
			if ((column == 0 || column == column_max || line == 0 || line == line_max) && (map[column][line] != '1'))
				return (0);
			line++;
		}
		column++;
	}
	return (1);
}

//ft_solve

//ft_caractere_nb

void ft_parsing(char **map, int fd_size)
{
	if (!ft_valid_map(map))
		ft_exit(4, 0, map);
	if (!ft_map_limit(map, fd_size - 1))
		ft_exit(3, 0, map);
}