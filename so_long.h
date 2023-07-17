#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_env
{
	char    **map;
	void    *mlx;
	void    *mlx_win;
	size_t  nb_move;
}   t_env;

void    ft_exit(int exit_code, char *arg, char **tab);
void    ft_parsing(char **map, int fd_size);
int     ft_close_window(t_env *env);

#endif
