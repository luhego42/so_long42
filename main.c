/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:45:49 by luhego            #+#    #+#             */
/*   Updated: 2023/07/20 16:59:39 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_print_map(char **map, int fd_size)
{
	int	column;

	column = 0;
	while (column != fd_size)
	{
		ft_putstr_fd(map[column], 1);
		write(1, "\n", 1);
		column++;
	}
}

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
	//	if (env->img)
	//		free(img);
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
	int		fd_size;

	if (argc == 2)
	{
		if (!ft_valid_file(argv[1], &fd_size, &env.map))
			return (0);
		if (!ft_fill_map(&fd_size, argv[1], env.map))
			return (0);
		env.mlx = 0;
		env.mlx_win = 0;
		ft_parsing(&env, fd_size);
		env.mlx = mlx_init();
		if (!env.mlx)
			ft_exit("Error\nFail init map.\n", &env);
		env.mlx_win = mlx_new_window(env.mlx, 1920, 1080, "Slide_Pingu");
		if (!env.mlx_win)
			ft_exit("Error\nFail open window.\n", &env);
		ft_refresh_win(&env);
		mlx_hook(env.mlx_win, 17, 1L << 3, ft_close_window, &env);
		//mlx_key_hook (env.mlx_win, ft_keyboard, &env);
		mlx_loop(env.mlx);
		ft_print_map(env.map, fd_size);
		ft_exit(0, &env);
	}
	return (0);
}
