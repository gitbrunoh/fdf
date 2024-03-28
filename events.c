/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:10:49 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 11:52:42 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	window_close(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	clean_up(fdf);
	exit(0);
}

void	handle_altscale(int keycode, t_fdf *fdf)
{
	if (keycode == 97)
		fdf->alt_scale_factor -= 1;
	else if (keycode == 115)
		fdf->alt_scale_factor += 1;
	redraw(fdf);
}

int	keys(int keycode, t_fdf *fdf)
{
	fdf = (void *)(fdf);
	if (keycode == ESC_K)
		handle_esc(fdf);
	else if (keycode == 116 || keycode == 114)
		handle_projection(fdf, keycode);
	else if (keycode == 111 || keycode == 105)
		handle_zoom(fdf, keycode);
	else if (keycode == 65362 || keycode == 65364 || keycode == 65361 || \
	keycode == 65363)
		handle_move(keycode, fdf);
	else if (keycode == 120 || keycode == 121 || keycode == 122 || \
	keycode == 100)
		handle_rotation(keycode, fdf);
	else if (keycode == 97 || keycode == 115)
		handle_altscale(keycode, fdf);
	return (0);
}

void	display_infos(t_fdf *fdf)
{
	mlx_string_put (fdf->mlx, fdf->win, 80, 50, 0xFFFFFF, \
	"FDF BONUS - brunhenr");
	mlx_string_put (fdf->mlx, fdf->win, 50, 80, 0xFFFFFF, \
	"PRESS:");
	mlx_string_put (fdf->mlx, fdf->win, 50, 110, 0xFFFFFF, \
	"<t> - TOP VIEW or <r> RETURN ISO");
	mlx_string_put (fdf->mlx, fdf->win, 50, 140, 0xFFFFFF, \
	"<i> - ZOOM IN or <o> - ZOOM OUT");
	mlx_string_put (fdf->mlx, fdf->win, 50, 170, 0xFFFFFF, \
	"<x> - ROTATE X or <y> - ROTATE Y or <z> - ROTATE Z");
	mlx_string_put (fdf->mlx, fdf->win, 50, 200, 0xFFFFFF, \
	"<d> - BACK TO DEFAULT ANGLE");
	mlx_string_put (fdf->mlx, fdf->win, 50, 230, 0xFFFFFF, \
	"<s> - SCRETCH or <a> - FLATTEN");
	mlx_string_put (fdf->mlx, fdf->win, 50, 260, 0xFFFFFF, \
	"USE ARROWS TO MODE THE MODEL");
}

int	redraw(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (fdf->img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = NULL;
	}
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bbp, \
	&fdf->line_length, &fdf->endian);
	fdf->matrix = alloc_fill_matrix (fdf, fdf->stack);
	draw (fdf);
	free_matrix (fdf->matrix, fdf->nbr_of_rows);
	mlx_put_image_to_window (fdf->mlx, fdf->win, fdf->img, 0, 0);
	display_infos (fdf);
	return (0);
}
