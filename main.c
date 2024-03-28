/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:04:51 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 10:08:13 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_inicialization(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		clean_up(fdf);
		perror("Error: mlx_init");
		exit (1);
	}
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf - brunhenr");
	if (!fdf->win)
	{
		clean_up(fdf);
		perror("Error: mlx_new_window");
		exit (1);
	}
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
	{
		clean_up(fdf);
		perror("Error: mlx_new_image");
		exit (1);
	}
}

void	draw_lines_and_run_mlx(t_fdf *fdf)
{
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bbp, \
	&fdf->line_length, &fdf->endian);
	if (!fdf->addr)
	{
		clean_up(fdf);
		perror("Error: mlx_get_data_addr");
		exit (1);
	}
	mlx_hook (fdf->win, 17, 0, window_close, fdf);
	mlx_key_hook (fdf->win, keys, fdf);
	mlx_expose_hook(fdf->win, redraw, fdf);
	mlx_loop (fdf->mlx);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;

	if (argc == 2)
	{
		fdf = malloc (sizeof(t_fdf));
		if (!fdf)
			return (1);
		fd = open_file (argv[1], fdf);
		fdf->stack = read_file (fd, fdf);
		close (fd);
		view_settings (fdf);
		mlx_inicialization (fdf);
		draw_lines_and_run_mlx (fdf);
	}
	else
		return (1);
	return (0);
}
