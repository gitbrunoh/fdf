/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:55:10 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 09:57:18 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_esc(t_fdf *fdf)
{
	clean_up(fdf);
	exit(0);
}

void	handle_projection(t_fdf *fdf, int keycode)
{
	if (keycode == 114)
		fdf->is_iso = 1;
	else if (keycode == 116)
		fdf->is_iso = 0;
	redraw(fdf);
}

void	handle_zoom(t_fdf *fdf, int keycode)
{
	if (keycode == 111)
	{
		if (fdf->zoom < 2)
			fdf->zoom = 1;
		else
			fdf->zoom -= 2;
	}
	if (keycode == 105)
		fdf->zoom += 2;
	redraw(fdf);
}

void	handle_move(int keycode, t_fdf *fdf)
{
	if (keycode == 65362)
		fdf->y_root -= 10;
	else if (keycode == 65364)
		fdf->y_root += 10;
	else if (keycode == 65361)
		fdf->x_root -= 10;
	else if (keycode == 65363)
		fdf->x_root += 10;
	redraw(fdf);
}

void	handle_rotation(int keycode, t_fdf *fdf)
{
	if (keycode == 120)
		fdf->alpha += 0.06;
	else if (keycode == 121)
		fdf->beta += 0.06;
	else if (keycode == 122)
		fdf->teta += 0.06;
	else if (keycode == 100)
	{
		fdf->alpha = 0;
		fdf->beta = 0;
		fdf->teta = 0;
	}
	redraw(fdf);
}
