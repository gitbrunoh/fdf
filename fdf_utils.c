/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:01:16 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 09:50:51 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(char *file, t_fdf *fdf)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		free (fdf);
		exit (1);
	}
	return (fd);
}

int	count_tokens_sep(char *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str[i] != sep && str[i] != '\0')
		count++;
	while (str[i])
	{
		if (str[i] == sep && str[i + 1] != sep && str[i + 1] != '\0' \
		&& str[i + 1] != '\n')
			count++;
		i++;
	}
	return (count);
}

int	ft_atoi_hex(const char *str)
{
	int	result;
	int	sign;
	int	digit_value;

	result = 0;
	sign = 1;
	while (*str == '0' || *str == 'x' )
		++str;
	while (*str)
	{
		digit_value = -1;
		if (*str >= '0' && *str <= '9')
			digit_value = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit_value = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit_value = *str - 'A' + 10;
		if (digit_value >= 16 || digit_value == -1)
			return (0);
		result = result * 16 + digit_value;
		++str;
	}
	return (result * sign);
}

void	find_altitude(t_fdf *fdf, t_matrix **arrays)
{
	int	min_altitude;
	int	max_altitude;
	int	i;
	int	j;	

	i = 0;
	j = 0;
	min_altitude = INT_MAX;
	max_altitude = INT_MIN;
	while (i < fdf->nbr_of_rows)
	{
		j = 0;
		while (j < fdf->nbr_of_cols)
		{
			if (arrays[i][j].z.alt < min_altitude)
				min_altitude = arrays[i][j].z.alt;
			if (arrays[i][j].z.alt > max_altitude)
				max_altitude = arrays[i][j].z.alt;
			j++;
		}
		i++;
	}
	fdf->max_alt = max_altitude;
	fdf->min_alt = min_altitude;
}
