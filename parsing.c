/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:00:22 by luhego            #+#    #+#             */
/*   Updated: 2023/07/25 19:00:55 by luhego           ###   ########.fr       */
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

/*static int	ft_flood_fill(t_env *env)
{
}
*/
static int	ft_caractere_nb(t_env *env)
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

void	ft_parsing(t_env *env, int fd_size)
{
	if (!ft_valid_map(env->map))
		ft_exit("Error\nMap letter incorrect.\n", env);
	if (!ft_map_limit(env->map, fd_size - 1))
		ft_exit("Error\nMap not surrounded by walls.\n", env);
	if (!ft_caractere_nb(env))
		ft_exit("Error\nMap need one entry, exit and min one item.\n", env);
//	if (!ft_flood_fill(env))
//		ft_exit("Error\nMap cannot be resolved", env);
}
