/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:00:19 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 10:00:58 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	default_angle(t_fdf *fdf)
{
	int		degress;
	double	radians;
	double	pi;

	pi = 3.14159265358979323846;
	degress = DEFAULT_ANGLE;
	radians = degress * (pi / 180);
	fdf->def_ang = radians;
}

void	view_settings(t_fdf *fdf)
{
	if (fdf->nbr_of_cols >= 300)
		fdf->zoom = 1;
	else if (fdf->nbr_of_cols >= 100)
		fdf->zoom = 10;
	else
		fdf->zoom = 30;
	fdf->x_root = (WIDTH / 2) - (fdf->nbr_of_cols / 2);
	fdf->y_root = (HEIGHT / 5) - (fdf->nbr_of_rows / 2);
	fdf->is_iso = 1;
	fdf->alt_scale_factor = ALT_SCL_FCTR;
	default_angle(fdf);
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->teta = 0;
}
