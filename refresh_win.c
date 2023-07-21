/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:49:40 by luhego            #+#    #+#             */
/*   Updated: 2023/07/21 19:14:01 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			printf("%d, %d\n", x * 64, y * 64);
			if (map[y][x] == 'E' && !env->items)
				mlx_put_image_to_window(env->mlx, env->mlx_win, env->mlx_xpm.open_exit, x * 64, y * 64);
			else if (map[y][x] == 'E')
				mlx_put_image_to_window(env->mlx, env->mlx_win, env->mlx_xpm.closed_exit, x * 64, y * 64);
			else if (map[y][x] == '1')
				mlx_put_image_to_window(env->mlx, env->mlx_win, env->mlx_xpm.wall, x * 64, y * 64);
			else if (map[y][x] == '0')
				mlx_put_image_to_window(env->mlx, env->mlx_win, env->mlx_xpm.floor, x * 64, y * 64);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(env->mlx, env->mlx_win, env->mlx_xpm.player, x * 64, y * 64);
			x++;
		}
		y++;
	}
}
