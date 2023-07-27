/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fcnt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:22:20 by luhego            #+#    #+#             */
/*   Updated: 2023/07/27 20:12:44 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_get_player_location(t_env *env, int *player_y, int *player_x)
{
	int	y;
	int	x;

	y = 0;
	while (env->solving_map[y])
	{
		x = 0;
		while (env->solving_map[y][x])
		{
			if (env->solving_map[y][x] == 'P')
			{
				*player_y = y;
				*player_x = x;
			}
			x++;
		}
		y++;
	}
}

static void	ft_get_player(t_env *env, char **player, char **path, char move)
{
	int	y;
	int	x;

	y = 0;
	while (env->map[y])
	{
		x = 0;
		while (env->map[y][x])
		{
			if (env->map[y][x] == 'P')
			{
				*player = &env->map[y][x];
				if (move == UP)
					*path = &env->map[y - 1][x];
				if (move == DOWN)
					*path = &env->map[y + 1][x];
				if (move == LEFT)
					*path = &env->map[y][x - 1];
				if (move == RIGHT)
					*path = &env->map[y][x + 1];
			}
			x++;
		}
		y++;
	}
}

int	ft_map_is_solved(t_env *env)
{
	int	y;
	int	x;

	y = 0;
	while (env->solving_map[y])
	{
		x = 0;
		while (env->solving_map[y][x])
		{
			if (env->solving_map[y][x] == 'C')
				return (0);
			if (env->solving_map[y][x] == '0')
				return (0);
			if (env->solving_map[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static void	ft_move_image(t_env *env, char move)
{
	char	*player;
	char	*path;

	player = 0;
	path = 0;
	ft_get_player(env, &player, &path, move);
	if (*path == '0')
	{
		env->nb_move += 1;
		ft_printf("%i\n", env->nb_move);
		ft_swap_image(player, path);
	}
	else if (*path == 'C')
	{
		env->nb_move += 1;
		ft_printf("%i\n", env->nb_move);
		ft_swap_image(player, path);
		env->items -= 1;
	}
	else if (*path == 'E' && env->items == 0)
	{
		ft_putstr_fd("Well slide pingou, you did it !\n", 1);
		ft_exit(0, env);
	}
}

int	ft_keyboard(int keycode, t_env *env)
{
	if (keycode == 65307)
		ft_exit(0, env);
	else if (keycode == 'a' || keycode == 'd' \
	|| keycode == 'w' || keycode == 's')
		ft_move_image(env, keycode);
	ft_refresh_win(env);
	return (0);
}
