/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:08:36 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 09:58:31 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		dst = fdf->addr + (y * fdf->line_length + x * (fdf->bbp / 8));
		*(unsigned int *)dst = color;
	}
}

t_parameter	*def_parameter(t_point *a, t_point *b)
{
	t_parameter	*parameter;

	parameter = malloc(sizeof(t_parameter));
	parameter->dx = abs(b->x - a->x);
	parameter->dy = -abs(b->y - a->y);
	parameter->decision_var = parameter->dx + parameter->dy;
	if (a->x < b->x)
		parameter->inc_x = 1;
	else if (a->x >= b->x)
		parameter->inc_x = -1;
	if (a->y < b->y)
		parameter->inc_y = 1;
	else if (a->y >= b->y)
		parameter->inc_y = -1;
	return (parameter);
}

void	interplt_clr(t_fdf *fdf, t_point *a, t_point *b, float ratio)
{
	int		r;
	int		g;
	int		blue;

	if (a->z <= b->z)
	{
		r = ((a->color >> 16) & 0xFF) + (((b->color >> 16) & 0xFF) \
		- ((a->color >> 16) & 0xFF)) * ratio;
		g = ((a->color >> 8) & 0xFF) + (((b->color >> 8) & 0xFF) \
		- ((a->color >> 8) & 0xFF)) * ratio;
		blue = (a->color & 0xFF) + ((b->color & 0xFF) \
		- (a->color & 0xFF)) * ratio;
	}
	if (a->z > b->z)
	{
		r = ((a->color >> 16) & 0xFF) - (((a->color >> 16) & 0xFF) \
		- ((b->color >> 16) & 0xFF)) * ratio;
		g = ((a->color >> 8) & 0xFF) - (((a->color >> 8) & 0xFF) \
		- ((b->color >> 8) & 0xFF)) * ratio;
		blue = (a->color & 0xFF) - ((a->color & 0xFF) \
		- (b->color & 0xFF)) * ratio;
	}
	fdf->color = (r << 16) | (g << 8) | blue;
}

void	update_points(t_point *a, t_parameter *parameter)
{
	parameter->decision_var_2 = parameter->decision_var * 2;
	if (parameter->decision_var_2 >= parameter->dy)
	{
		parameter->decision_var += parameter->dy;
		a->x += parameter->inc_x;
	}
	if (parameter->decision_var_2 <= parameter->dx)
	{
		parameter->decision_var += parameter->dx;
		a->y += parameter->inc_y;
	}
}

void	rasterization(t_fdf *fdf, t_point *a, t_point *b)
{
	t_parameter	*parameter;
	int			curr_step;
	int			total_steps;
	float		ratio;

	parameter = def_parameter (a, b);
	curr_step = 0;
	if (abs(parameter->dx) > abs(parameter->dy))
		total_steps = abs(parameter->dx);
	else
		total_steps = abs(parameter->dy);
	while ((a->x != b->x) || (a->y != b->y))
	{
		ratio = (float)curr_step / total_steps;
		interplt_clr (fdf, a, b, ratio);
		my_mlx_pixel_put (fdf, a->x, a->y, fdf->color);
		update_points (a, parameter);
		curr_step++;
	}
	free (parameter);
	free (a);
	free (b);
}
