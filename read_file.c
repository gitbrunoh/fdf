/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:08:23 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 09:59:38 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_line_error(int nbr_of_cols, int i, t_stack **stack)
{
	if (nbr_of_cols != i)
	{
		free_stack(*stack);
		return (1);
	}
	return (0);
}

int	split_line_to_stack(char *line, t_stack **stack, int *nbr_of_cols)
{
	int		i;
	char	**split;
	char	**sec_split;	

	i = 0;
	split = ft_split(line, ' ');
	while (split[i] != NULL)
	{
		sec_split = ft_split(split[i], ',');
		if (build_stack(sec_split, stack))
		{
			free_split(sec_split);
			free_split(split);
			return (1);
		}
		free_split(sec_split);
		i++;
	}
	free_split(split);
	if (check_line_error(*nbr_of_cols, i, stack) == 1)
		return (1);
	return (0);
}

t_stack	*read_file(int fd, t_fdf *fdf)
{
	char	*line;
	t_stack	*stack;
	int		count_rows;

	count_rows = 0;
	stack = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		ext_read_file_errors(2, fdf);
	fdf->nbr_of_cols = count_tokens_sep(line, ' ');
	while (line != NULL)
	{
		count_rows++;
		if (split_line_to_stack(line, &stack, &fdf->nbr_of_cols))
		{
			free(line);
			ext_read_file_errors(3, fdf);
		}
		free(line);
		line = get_next_line(fd);
	}
	fdf->nbr_of_rows = count_rows;
	free(line);
	close(fd);
	return (stack);
}
