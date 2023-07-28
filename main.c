/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:45:49 by luhego            #+#    #+#             */
/*   Updated: 2023/07/28 17:38:06 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_destroy_sprite(t_env *env)
{
	if (ft_xpm_exist(0) == 1)
	{
		if (env->mlx_xpm.opened_exit != 0)
			mlx_destroy_image(env->mlx, env->mlx_xpm.opened_exit);
		if (env->mlx_xpm.closed_exit != 0)
			mlx_destroy_image(env->mlx, env->mlx_xpm.closed_exit);
		if (env->mlx_xpm.player != 0)
			mlx_destroy_image(env->mlx, env->mlx_xpm.player);
		if (env->mlx_xpm.floor != 0)
			mlx_destroy_image(env->mlx, env->mlx_xpm.floor);
		if (env->mlx_xpm.wall != 0)
			mlx_destroy_image(env->mlx, env->mlx_xpm.wall);
		if (env->mlx_xpm.item != 0)
			mlx_destroy_image(env->mlx, env->mlx_xpm.item);
	}
}

void	ft_exit(char *str_error, t_env *env)
{
	if (str_error)
		ft_putstr_fd(str_error, 2);
	if (env)
	{
		if (env->map)
			ft_free_double_tab(env->map);
		if (env->solving_map)
			ft_free_double_tab(env->solving_map);
		ft_destroy_sprite(env);
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

void	ft_init_xpm(t_env *env, int *img_width, int *img_height)
{
	env->mlx_xpm.opened_exit = mlx_xpm_file_to_image(env->mlx, \
	"./xpm/opened_exit.xpm", img_width, img_height);
	if (env->mlx_xpm.opened_exit == 0)
		ft_exit("Error\nWrong file xpm.\n", env);
	env->mlx_xpm.closed_exit = mlx_xpm_file_to_image(env->mlx, \
	"./xpm/closed_exit.xpm", img_width, img_height);
	if (env->mlx_xpm.closed_exit == 0)
		ft_exit("Error\nWrong file xpm.\n", env);
	env->mlx_xpm.player = mlx_xpm_file_to_image(env->mlx, \
	"./xpm/player.xpm", img_width, img_height);
	if (env->mlx_xpm.player == 0)
		ft_exit("Error\nWrong file xpm.\n", env);
	env->mlx_xpm.wall = mlx_xpm_file_to_image(env->mlx, \
	"./xpm/wall.xpm", img_width, img_height);
	if (env->mlx_xpm.wall == 0)
		ft_exit("Error\nWrong file xpm.\n", env);
	env->mlx_xpm.floor = mlx_xpm_file_to_image(env->mlx, \
	"./xpm/floor.xpm", img_width, img_height);
	if (env->mlx_xpm.floor == 0)
		ft_exit("Error\nWrong file xpm.\n", env);
	env->mlx_xpm.item = mlx_xpm_file_to_image(env->mlx, \
	"./xpm/item.xpm", img_width, img_height);
	if (env->mlx_xpm.floor == 0)
		ft_exit("Error\nWrong file xpm.\n", env);
}

static void	ft_init_env(t_env *env, char *str, int map_height, int map_width)
{
	if (!ft_valid_file(str, &map_height, &env->map))
		exit(0);
	if (!ft_fill_map(&map_height, str, env->map))
		exit(0);
	env->mlx = 0;
	env->mlx_win = 0;
	env->nb_move = 0;
	env->items = 0;
	env->mlx_xpm.opened_exit = 0;
	env->mlx_xpm.closed_exit = 0;
	env->mlx_xpm.player = 0;
	env->mlx_xpm.wall = 0;
	env->mlx_xpm.floor = 0;
	env->mlx_xpm.item = 0;
	env->solving_map = 0;
	ft_parsing(env, map_height, str);
	map_width = ft_strlen(env->map[0]);
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_exit("Error\nFail init map.\n", env);
	env->mlx_win = mlx_new_window(env->mlx, \
	map_width * 64, map_height * 64, "Slide_Pingu");
	if (!env->mlx_win)
		ft_exit("Error\nFail open window.\n", env);
}

int	main(int argc, char **argv)
{
	t_env	env;
	int		img_width;
	int		img_height;

	if (argc == 2)
	{
		ft_init_env(&env, argv[1], 0, 0);
		if (ft_xpm_exist(0) == -1)
			ft_exit("Error\nNo .xpm found.\n", &env);
		ft_init_xpm(&env, &img_width, &img_height);
		ft_refresh_win(&env);
		mlx_hook(env.mlx_win, 17, 1L << 3, ft_close_window, &env);
		mlx_key_hook(env.mlx_win, ft_keyboard, &env);
		mlx_loop(env.mlx);
		ft_exit(0, &env);
	}
	return (0);
}
