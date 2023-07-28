/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:00:22 by luhego            #+#    #+#             */
/*   Updated: 2023/07/28 17:38:23 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_valid_map(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' \
			&& map[y][x] != 'C' && map[y][x] != 'E' && map[y][x] != 'P')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	ft_map_limit(char **map, int column_max)
{
	int	line_max;
	int	line;
	int	column;

	line_max = ft_strlen(map[0]) - 1;
	column = 0;
	while (map[column])
	{
		line = 0;
		while (map[column][line])
		{
			if ((column == 0 || column == column_max || line == 0 \
			|| line == line_max) && (map[column][line] != '1'))
				return (0);
			line++;
		}
		column++;
	}
	return (1);
}

static void	ft_flood_fill(t_env *env, int y, int x)
{
	if (env->solving_map[y][x] != '1' && env->solving_map[y][x] != 'P')
	{
		env->solving_map[y][x] = 'P';
		ft_flood_fill(env, y, x + 1);
		ft_flood_fill(env, y, x - 1);
		ft_flood_fill(env, y + 1, x);
		ft_flood_fill(env, y - 1, x);
	}
}

static int	ft_char_nb(t_env *env)
{
	int	e;
	int	p;
	int	x;
	int	y;

	e = 0;
	p = 0;
	y = -1;
	while (env->map[++y])
	{
		x = -1;
		while (env->map[y][++x])
		{
			if (env->map[y][x] == 'E')
				e++;
			else if (env->map[y][x] == 'P')
				p++;
			else if (env->map[y][x] == 'C')
				env->items++;
		}
	}
	if (e != 1 || p != 1 || env->items < 1)
		return (0);
	return (1);
}

void	ft_parsing(t_env *env, int fd_size, char *str)
{
	int	y;
	int	x;

	if (!ft_valid_map(env->map))
		ft_exit("Error\nMap letter incorrect.\n", env);
	if (!ft_map_limit(env->map, fd_size - 1))
		ft_exit("Error\nMap not surrounded by walls.\n", env);
	if (!ft_char_nb(env))
		ft_exit("Error\nMap need one entry, exit and min one item.\n", env);
	env->solving_map = malloc(sizeof(char *) * (fd_size + 1));
	if (!env->solving_map)
		ft_exit("Error\nMissing memory.\n", env);
	ft_fill_map(&fd_size, str, env->solving_map);
	ft_get_player_location(env, &y, &x);
	env->solving_map[y][x] = '0';
	ft_flood_fill(env, y, x);
	if (!ft_map_is_solved(env))
		ft_exit("Error\nMap cannot be resolved\n", env);
}
