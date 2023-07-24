/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:45:49 by luhego            #+#    #+#             */
/*   Updated: 2023/07/24 19:44:46 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_exit(char *str_error, t_env *env)
{
	char	**tab;
	int		i;

	if (str_error)
		ft_putstr_fd(str_error, 2);
	if (env)
	{
		tab = env->map;
		if (tab)
		{
			i = 0;
			while (tab[i])
			{
				free(tab[i]);
				i++;
			}
			free(tab);
		}
		if (env->mlx_xpm.opened_exit) // possible segfault on specific cases
		{
			mlx_destroy_image(env->mlx, env->mlx_xpm.opened_exit);
			mlx_destroy_image(env->mlx, env->mlx_xpm.closed_exit);
			mlx_destroy_image(env->mlx, env->mlx_xpm.player);
			mlx_destroy_image(env->mlx, env->mlx_xpm.floor);
			mlx_destroy_image(env->mlx, env->mlx_xpm.wall);
			mlx_destroy_image(env->mlx, env->mlx_xpm.item);
		}
		if (env->mlx_win)
			mlx_destroy_window(env->mlx, env->mlx_win);
		if (env->mlx)
		{
			mlx_destroy_display(env->mlx);
			free(env->mlx);
		}
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	t_env	env;
	int		map_height;
	int		map_width;

	if (argc == 2)
	{
		if (!ft_valid_file(argv[1], &map_height, &env.map))
			return (0);
		if (!ft_fill_map(&map_height, argv[1], env.map))
			return (0);
		env.mlx = 0;
		env.mlx_win = 0;
		ft_parsing(&env, map_height);
		map_width = ft_strlen(env.map[0]);
		env.mlx = mlx_init();
		if (!env.mlx)
			ft_exit("Error\nFail init map.\n", &env);
		env.mlx_win = mlx_new_window(env.mlx, map_width * 64, map_height * 64, "Slide_Pingu");
		if (!env.mlx_win)
			ft_exit("Error\nFail open window.\n", &env);
		ft_init_xpm(&env);
		ft_refresh_win(&env);
		mlx_hook(env.mlx_win, 17, 1L << 3, ft_close_window, &env);
		mlx_key_hook(env.mlx_win, ft_keyboard, &env);
		mlx_loop(env.mlx);
		ft_exit(0, &env);
	}
	return (0);
}
