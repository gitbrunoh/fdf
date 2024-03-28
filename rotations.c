/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:11:46 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 07:51:08 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(int *x, int *y, int z, double def_ang)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(def_ang);
	*y = (previous_x + previous_y) * sin(def_ang) - z;
}

void	x_rotation(int *y, int *z, double gama)
{
	*y = *y * cos(gama) + *z * sin(gama);
	*z = -(*y) * sin(gama) + *z * (cos(gama));
}

void	y_rotation(int *x, int *z, double gama)
{
	*x = *x * cos(gama) + *z * sin(gama);
	*z = -(*x) * sin(gama) + *z * (cos(gama));
}

void	z_rotation(int *x, int *y, double gama)
{
	*x = *x * cos(gama) - *y * sin(gama);
	*y = (*x) * sin(gama) + *y * (cos(gama));
}

t_point	*projection(t_point *p, t_fdf *fdf)
{
	p->x *= fdf->zoom;
	p->y *= fdf->zoom;
	x_rotation (&p->y, &p->z, fdf->alpha);
	y_rotation (&p->x, &p->z, fdf->beta);
	z_rotation (&p->x, &p->y, fdf->teta);
	if (fdf->is_iso == 1)
		iso (&p->x, &p->y, p->z, fdf->def_ang);
	p->x += fdf->x_root;
	p->y += fdf->y_root;
	return (p);
}
