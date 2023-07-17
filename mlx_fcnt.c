#include "so_long.h"

int ft_close_window(t_env *env)
{
	mlx_destroy_window(env->mlx, env->mlx_win);
	ft_exit(0, 0, env->map);
	return (0);
}
/*
ft_mouse()

ft_keyboard()*/