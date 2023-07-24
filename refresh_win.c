/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:49:40 by luhego            #+#    #+#             */
/*   Updated: 2023/07/24 14:46:08 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_sprite(t_env *env, char c, int y, int x)
{
	if (c == 'E' && !env->items)
		mlx_put_image_to_window(env->mlx, env->mlx_win, \
		env->mlx_xpm.opened_exit, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(env->mlx, env->mlx_win, \
		env->mlx_xpm.closed_exit, x, y);
	else if (c == '1')
		mlx_put_image_to_window(env->mlx, env->mlx_win, \
		env->mlx_xpm.wall, x, y);
	else if (c == '0')
		mlx_put_image_to_window(env->mlx, env->mlx_win, \
		env->mlx_xpm.floor, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(env->mlx, env->mlx_win, \
		env->mlx_xpm.player, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(env->mlx, env->mlx_win, \
		env->mlx_xpm.item, x, y);
}

void	ft_refresh_win(t_env *env)
{
	char	**map;
	int		y;
	int		x;

	y = 0;
	map = env->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			ft_print_sprite(env, map[y][x], y * 64, x * 64);
			x++;
		}
		y++;
	}
}
