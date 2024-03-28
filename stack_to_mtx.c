/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_to_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:11:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/24 21:13:01 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fillline_stack_to_mtx(t_matrix *mtx_line, t_stack **stack, t_fdf *fdf)
{
	int	cols;

	cols = fdf->nbr_of_cols;
	while (cols-- > 0)
	{
		if (*stack == NULL)
			return ;
		mtx_line[cols].z.alt = (*stack)->z->alt;
		mtx_line[cols].z.color = (*stack)->z->color;
		*stack = (*stack)->next;
	}
}

t_matrix	**alloc_fill_matrix(t_fdf *fdf, t_stack *stack)
{
	t_matrix	**matrix;
	int			rows;
	int			cols;
	int			temp_rows;

	rows = fdf->nbr_of_rows;
	cols = fdf->nbr_of_cols;
	temp_rows = rows;
	matrix = (t_matrix **)malloc(sizeof(t_matrix *) * (rows + 1));
	if (!matrix)
		return (NULL);
	while (rows-- > 0)
	{
		matrix[rows] = (t_matrix *)malloc(sizeof(t_matrix) * (cols));
		if (!matrix[rows])
			return (NULL);
		fillline_stack_to_mtx(matrix[rows], &stack, fdf);
	}
	matrix[temp_rows] = NULL;
	return (matrix);
}
