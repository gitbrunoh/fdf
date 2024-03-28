/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:50:20 by brunhenr          #+#    #+#             */
/*   Updated: 2024/03/28 08:51:56 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESC_K 65307
# define WIDTH 3840
# define HEIGHT 2160
# define ALT_SCL_FCTR 10
# define RED_CONSTANT 100
# define GREEN_MIN 0
# define GREEN_MAX 140
# define BLUE_MIN 0
# define BLUE_MAX 240
# define DEFAULT_ANGLE 45

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"
# include "libft/libft.h"

typedef struct s_z
{
	int	alt;
	int	color;
}	t_z;

typedef struct s_stack
{
	t_z				*z;
	struct s_stack	*next;
}	t_stack;

typedef struct s_matrix
{
	t_z	z;
}	t_matrix;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bbp;
	int			line_length;
	int			endian;
	int			nbr_of_rows;
	int			nbr_of_cols;
	t_stack		*stack;
	t_matrix	**matrix;
	int			zoom;
	int			alt_scale_factor;
	bool		is_iso;
	int			color;
	int			x_root;
	int			y_root;
	double		def_ang;
	double		alpha;
	double		beta;
	double		teta;
	int			max_alt;
	int			min_alt;
}	t_fdf;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct t_parameter
{
	int	dx;
	int	dy;
	int	decision_var;
	int	decision_var_2;
	int	inc_x;
	int	inc_y;
}	t_parameter;

//**utils**
int			count_tokens_sep(char *str, char sep);
int			ft_atoi_hex(const char *str);
int			open_file(char *file, t_fdf *fdf);
void		find_altitude(t_fdf *fdf, t_matrix **arrays);
void		ft_printmatrix(t_matrix **matrix, t_fdf *fdf);
//**frees**
void		clean_up(t_fdf *fdf);
void		free_split(char **split);
void		free_stack(t_stack *stack);
void		free_matrix(t_matrix **matrix, int nbr_of_rows);
//**errors**
void		ext_read_file_errors(int error_nbr, t_fdf *fdf);
void		check_errors(int checker_fd);
//**draw**
void		rasterization(t_fdf *fdf, t_point *a, t_point *b);
void		draw(t_fdf *fdf);
//**events**
int			window_close(void *param);
void		handle_projection(t_fdf *fdf, int keycode);
void		handle_zoom(t_fdf *fdf, int keycode);
void		handle_move(int keycode, t_fdf *fdf);
void		handle_rotation(int keycode, t_fdf *fdf);
void		handle_esc(t_fdf *fdf);
int			keys(int keycode, t_fdf *fdf);
int			redraw(void *param);
//**bonus events and extra**
void		infos_display(t_fdf *fdf);
//**parsing**
int			build_stack(char **sec_split, t_stack **stack);
t_stack		*read_file(int fd, t_fdf *fdf);
t_matrix	**alloc_fill_matrix(t_fdf *fdf, t_stack *stack);
//**visuals**
void		view_settings(t_fdf *fdf);
void		default_angle(t_fdf *fdf);
//**rotations**
void		iso(int *x, int *y, int z, double def_angle);
void		x_rotation(int *y, int *z, double gama);
void		y_rotation(int *x, int *z, double gama);
void		z_rotation(int *x, int *y, double gama);
t_point		*projection(t_point *p, t_fdf *fdf);

#endif
