/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:45:36 by brunhenr          #+#    #+#             */
/*   Updated: 2023/11/16 13:38:20 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
int		is_there_nl(t_list *box);
void	put_read_on_the_box(t_list **box, char *buffer, int count);
void	manage_read(t_list **box, int *count, int fd);
void	malloc_line(char **line, t_list *box);
void	define_line(t_list *box, char **line);
void	set_box(t_list **box);
void	ft_lstclear(t_list *lst, int mode);
t_list	*ft_lstlast(t_list *lst);
size_t	ft_strlen(const char *str);

#endif
