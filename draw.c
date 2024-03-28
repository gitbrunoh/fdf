/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:11:03 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/27 20:27:46 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*point_init(int x, int y, t_fdf *fdf)
{
	t_point	*p;

	p = (t_point *)malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	p->z = fdf->matrix[y][x].z.alt * fdf->alt_scale_factor;
	p->y = y;
	p->x = x;
	return (p);
}

int	calculate_color(t_fdf *fdf, int x, int y)
{
	int		alt;
	int		green;
	int		blue;
	float	ratio;

	if (fdf->matrix[y][x].z.color == -1)
	{
		alt = fdf->matrix[y][x].z.alt;
		ratio = ((float)alt - fdf->min_alt) / (fdf->max_alt - fdf->min_alt);
		green = GREEN_MIN * (1 - ratio) + GREEN_MAX * ratio;
		blue = BLUE_MIN * (1 - ratio) + BLUE_MAX * ratio;
		return ((RED_CONSTANT << 16) | (green << 8) | blue);
	}
	else
		return (fdf->matrix[y][x].z.color);
}

void	dash_y_direction(t_fdf *fdf, int x, int y)
{
	t_point	*start;
	t_point	*end;

	start = projection(point_init(x, y, fdf), fdf);
	end = projection(point_init(x, y + 1, fdf), fdf);
	start->color = calculate_color(fdf, x, y);
	end->color = calculate_color(fdf, x, y + 1);
	rasterization (fdf, start, end);
}

void	dash_x_direction(t_fdf *fdf, int x, int y)
{
	t_point	*start;
	t_point	*end;

	start = projection(point_init(x, y, fdf), fdf);
	end = projection(point_init(x + 1, y, fdf), fdf);
	start->color = calculate_color(fdf, x, y);
	end->color = calculate_color(fdf, x + 1, y);
	rasterization (fdf, start, end);
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	find_altitude (fdf, fdf->matrix);
	y = 0;
	while (y < fdf->nbr_of_rows)
	{
		x = 0;
		while (x < fdf->nbr_of_cols)
		{
			if (x < fdf->nbr_of_cols - 1)
				dash_x_direction(fdf, x, y);
			if (y < fdf->nbr_of_rows - 1)
				dash_y_direction(fdf, x, y);
			x++;
		}
		y++;
	}
}
