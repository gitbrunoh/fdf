/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:02:54 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 09:54:29 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_up(t_fdf *fdf)
{
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
	}
	if (fdf->mlx)
	{
		mlx_loop_end(fdf->mlx);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	free_stack (fdf->stack);
	fdf->stack = NULL;
	free(fdf);
}

void	free_stack(t_stack *stack)
{
	t_stack	*tmp;

	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp->z);
		free(tmp);
	}
}

void	free_matrix(t_matrix **matrix, int nbr_of_rows)
{
	int	i;

	i = 0;
	while (i < nbr_of_rows)
	{
		free(matrix[i]);
		i++;
	}
	free (matrix);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
