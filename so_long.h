/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:22:09 by luhego            #+#    #+#             */
/*   Updated: 2023/07/20 16:59:51 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_mlx_img
{
	void	*open_exit;
	void	*close_exit;
	void	*player;
	void	*floor;
	void	*wall;
	
}	t_mlx_xpm;

typedef struct s_env
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	size_t	items;
	size_t	nb_move;
}	t_env;

void	ft_exit(char *str_error, t_env *env);
void	ft_parsing(t_env *env, int fd_size);
void	ft_fd_size(int fd, int *fd_size);
int		ft_close_window(t_env *env);
int		ft_valid_file(char *file, int *fd_size, char ***map);
int		ft_fill_map(int *fd_size, char *file, char **map);

#endif
