/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:58:34 by brunhenr          #+#    #+#             */
/*   Updated: 2023/11/16 13:55:17 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	malloc_line(char **line, t_list *box)
{
	int	i;
	int	len;

	len = 0;
	while (box)
	{
		i = 0;
		while (box -> content[i] != '\0')
		{
			if (box -> content[i] == '\n')
			{
				len++;
				*line = malloc(sizeof(char) * (len + 1));
				return ;
			}
			i++;
			len++;
		}
		box = box -> next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
}

void	define_line(t_list *box, char **line)
{
	int	j;
	int	i;

	malloc_line(line, box);
	j = 0;
	while (box)
	{
		i = 0;
		while (box -> content[i] != '\0')
		{
			if (box -> content[i] == '\n')
			{
				(*line)[j++] = box -> content[i];
				(*line)[j] = '\0';
				return ;
			}
			(*line)[j++] = box -> content[i++];
		}
		box = box -> next;
	}
	(*line)[j] = '\0';
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	ft_lstclear(t_list *lst, int mode)
{
	t_list	*current;
	t_list	*next;

	if (lst == NULL)
		return ;
	if (mode == -1)
	{
		free(lst -> content);
		free(lst);
		return ;
	}
	current = lst;
	while (current)
	{
		free(current -> content);
		next = current -> next;
		free(current);
		current = next;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current && current -> next)
		current = current -> next;
	return (current);
}
