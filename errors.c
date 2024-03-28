/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:11:21 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/27 11:17:55 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ext_read_file_errors(int error_nbr, t_fdf *fdf)
{
	if (error_nbr == 2)
		ft_printf("Map error: get_next_line first call returned <NULL>\n");
	else if (error_nbr == 3)
		ft_printf("Stack allocation error or more columns than split tokens\n");
	free(fdf);
	exit (1);
}
