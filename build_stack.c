/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:12:24 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/24 21:13:01 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_node(t_stack **stack, t_stack *new_node)
{
	if (stack && new_node)
	{
		if (*stack == NULL)
			*stack = new_node;
		else
		{
			new_node->next = *stack;
			*stack = new_node;
		}
	}
}

int	build_stack(char **sec_split, t_stack **stack)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
	{
		free_stack(*stack);
		return (1);
	}
	new_node->z = (t_z *)malloc(sizeof(t_z));
	if (!(new_node->z))
	{
		free(new_node);
		free_stack(*stack);
		return (1);
	}
	new_node->z->alt = ft_atoi(sec_split[0]);
	if (sec_split[1] == NULL)
		new_node->z->color = -1;
	else
		new_node->z->color = ft_atoi_hex(sec_split[1]);
	new_node->next = NULL;
	add_node(stack, new_node);
	return (0);
}
