/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esantaca <esantaca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:29:12 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/24 12:30:15 by esantaca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_board
{
	char		*cells;
	int			size;
}				t_board;

typedef struct	s_position
{
	int			x;
	int			y;
}				t_position;

char			**validate(int argc, int fd);
void			solve(const char **tetraminos, const int initial_board_size);

#endif
