/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fcnt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:22:20 by luhego            #+#    #+#             */
/*   Updated: 2023/07/25 17:03:32 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_window(t_env *env)
{
	ft_exit(0, env);
	return (0);
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

static void	ft_swap_image(char *player, char *path)
{
	char	tmp;

	tmp = *player;
	*player = '0';
	*path = tmp;
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
