/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:45:49 by luhego            #+#    #+#             */
/*   Updated: 2023/04/11 17:49:47 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_fd_size(int fd)
{
	size_t  columnNext;
	size_t  column;
	int		count;
	char    *line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		column = ft_strlen(line);
		if (line[column - 1] == '\n')
			column--;
		count++;
		free(line);
		if ((line = get_next_line(fd)) && (columnNext = ft_strlen(line)))
		{
			if (line[columnNext - 1] == '\n')
				columnNext--;
		}
		if (columnNext != column)
			ft_exit(2, 0, 0);
	}
	free(line);
	return (count);
}

static void    ft_print_map(char **map, int fd_size)
{
	int column;

	column = 0;
	while (column != fd_size)
	{
		ft_putstr_fd(map[column], 1);
		write(1, "\n", 1);
		column++;
	}
}

void    ft_exit(int exit_code, char *arg, char **tab)
{
	int i;

    if (exit_code == 1)
		ft_putstr_fd("Error\nWrong file_type.\n", 1);
	if (exit_code == 2)
		ft_putstr_fd("Error\nWrong map.\n", 1);
	if (exit_code == 3)
		ft_putstr_fd("Error\nNot surround by wall\n", 1);
	if (exit_code == 4)
		ft_putstr_fd("Error\nLetter Map Error\n", 1);
	if (arg)
		perror(arg);
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
    exit(0);
}

int ft_valid_file(char *file, int *fd_size, char ***map)
{
	size_t  file_type;
	int     fd;

	file_type = ft_strlen(file) - 4;
	if (ft_strncmp(&file[file_type], ".ber", 4) != 0)
		ft_exit(1, 0, 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	*fd_size = ft_fd_size(fd);
	printf("fd_size = %i\n", *fd_size);
	*map = malloc(sizeof(char *) * (*fd_size + 1));
	if (!*map)
		ft_exit(0, "malloc", 0);
	close (fd);
	return (1);
}

int ft_fill_map(int *fd_size, char *file, char **map)
{
	int fd;
	int x;
	int y;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	x = 0;
	while (x != *fd_size)
	{
		map[x] = get_next_line(fd);
		y = ft_strlen(map[x]) - 1;
		if (map[x][y] == '\n')
			map[x][y] = 0;
		x++;
	}
	map[x] = 0;
	close (fd);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd_size;
	t_env   env;

	if (argc == 2)
	{
		if (!ft_valid_file(argv[1], &fd_size, &env.map))
			return (0);
		if (!ft_fill_map(&fd_size, argv[1], env.map))
			return (0);
		ft_parsing(env.map, fd_size);
		env.mlx = mlx_init();
		env.mlx_win = mlx_new_window(env.mlx, 1920, 1080, "Pingu_window");
		if (!env.mlx_win)
			return (0);
		mlx_hook(env.mlx_win, 17, 1L<<3, ft_close_window, &env);

		//mlx_key_hook (env.mlx_win, ft_keyboard, &env);
		//mlx_mouse_hook (mlx_win, ft_mouse, &env);
		mlx_loop(env.mlx);
		ft_print_map(env.map, fd_size);
		ft_exit(0, 0, env.map);
	}
	return (0);
}