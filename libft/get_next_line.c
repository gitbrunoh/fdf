/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:54:42 by brunhenr          #+#    #+#             */
/*   Updated: 2023/11/16 13:36:51 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*box = NULL;
	char			*line;
	int				count;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (box)
			ft_lstclear(box, -1);
		box = NULL;
		return (NULL);
	}
	count = 1;
	manage_read(&box, &count, fd);
	if (box == NULL)
		return (NULL);
	define_line(box, &line);
	set_box(&box);
	if (line[0] == '\0')
	{
		ft_lstclear(box, 0);
		box = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int	is_there_nl(t_list *box)
{
	t_list	*current_box;
	int		i;

	if (box == NULL)
		return (0);
	current_box = ft_lstlast(box);
	i = 0;
	while (current_box -> content[i])
	{
		if (current_box->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	put_read_on_the_box(t_list **box, char *buffer, int count)
{
	t_list	*new_box;
	t_list	*last_box;
	int		i;

	new_box = malloc(sizeof(t_list));
	if (new_box == NULL)
		return ;
	new_box -> next = NULL;
	new_box -> content = malloc(sizeof(char) * count + 1);
	if (new_box -> content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < count)
	{
		new_box -> content[i] = buffer[i];
		i++;
	}
	new_box -> content[i] = '\0';
	if (*box == NULL)
	{
		*box = new_box;
		return ;
	}
	last_box = ft_lstlast(*box);
	last_box -> next = new_box;
}

void	manage_read(t_list **box, int *count, int fd)
{
	char	*buffer;

	while (is_there_nl(*box) == 0 && *count != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		*count = read(fd, buffer, BUFFER_SIZE);
		if (*count == 0)
		{
			free(buffer);
			return ;
		}
		buffer[*count] = '\0';
		put_read_on_the_box(box, buffer, *count);
		free(buffer);
	}
}

void	set_box(t_list **box)

{
	t_list	*cleaned_box;
	t_list	*last_box;
	int		i;
	int		j;

	cleaned_box = malloc(sizeof(t_list));
	if (cleaned_box == NULL || box == NULL)
		return ;
	cleaned_box -> next = NULL;
	last_box = ft_lstlast(*box);
	i = 0;
	while (last_box -> content[i] && last_box -> content[i] != '\n')
		i++;
	if (last_box -> content && last_box -> content[i] == '\n')
		i++;
	cleaned_box->content = malloc(ft_strlen(last_box->content) - i + 1);
	if (cleaned_box -> content == NULL)
		return ;
	j = 0;
	while (last_box -> content[i])
		cleaned_box -> content[j++] = last_box -> content[i++];
	cleaned_box -> content[j] = '\0';
	ft_lstclear(*box, 0);
	*box = cleaned_box;
}
