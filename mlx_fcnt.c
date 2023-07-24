/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fcnt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:22:20 by luhego            #+#    #+#             */
/*   Updated: 2023/07/24 19:48:27 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_window(t_env *env)
{
	ft_exit(0, env);
	return (0);
}

int	ft_keyboard(int	keycode, t_env *env)
{
	if (keycode == 65307)
		ft_exit(0, env);
/*	if (keycode == 'a')
		ft_move_image(env);
	if (keycode == 'd')
		ft_move_image(env);
	if (keycode == 'w')
		ft_move_image(env);
	if (keycode == 's')
		ft_move_image(env);
	ft_refresh_win(env);*/
	return (0);
}
/*
ft_mouse()

t_keyboard()*/
