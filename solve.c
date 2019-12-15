/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esantaca <esantaca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:08:38 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/24 12:30:53 by esantaca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

static int		tetra_in_board(const int board_size,
				const char *tetramino,
				const int tetramino_coord,
				const char axis)
{
	int			character_index;
	int			character_coord;

	character_index = 0;
	character_coord = -1;
	while (tetramino[++character_index])
	{
		if (tetramino[character_index] != '.')
		{
			if (axis == 'x')
				character_coord = tetramino_coord + (character_index % 4);
			else
				character_coord = tetramino_coord + (character_index / 4);
			if (character_coord >= board_size)
				return (0);
		}
	}
	return (1);
}

static int		overlap(t_board *p_board,
				const char *tetramino,
				const t_position tetramino_position)
{
	int			character_index;
	int			board_position_x;
	int			board_position_y;
	int			board_index;

	character_index = -1;
	board_position_x = -1;
	board_position_y = -1;
	board_index = -1;
	while (tetramino[++character_index])
	{
		if (tetramino[character_index] != '.')
		{
			board_position_x = tetramino_position.x + (character_index % 4);
			board_position_y = tetramino_position.y + (character_index / 4);
			board_index = board_position_x + (p_board->size * board_position_y);
			if (p_board->cells[board_index] != '.')
				return (1);
		}
	}
	return (0);
}

static void		place(t_board *p_board,
				const char *tetramino,
				const t_position tetramino_position,
				const char tetramino_id)
{
	int			character_index;
	int			board_position_x;
	int			board_position_y;
	int			board_index;

	character_index = -1;
	board_position_x = -1;
	board_position_y = -1;
	board_index = -1;
	while (tetramino[++character_index])
	{
		if (tetramino[character_index] != '.')
		{
			board_position_x = tetramino_position.x + (character_index % 4);
			board_position_y = tetramino_position.y + (character_index / 4);
			board_index = board_position_x + (p_board->size * board_position_y);
			p_board->cells[board_index] = tetramino_id;
		}
	}
}

static int		solve_board(t_board *p_board,
				const char **tetraminos,
				const int tetramino_idx)
{
	const char	*tetramino;
	t_position	tetramino_pos;

	tetramino = tetraminos[tetramino_idx];
	tetramino_pos.x = -1;
	tetramino_pos.y = -1;
	if (!(tetramino))
		return (1);
	while (tetra_in_board(p_board->size, tetramino, ++tetramino_pos.y, 'y'))
	{
		while (tetra_in_board(p_board->size, tetramino, ++tetramino_pos.x, 'x'))
		{
			if (!overlap(p_board, tetramino, tetramino_pos))
			{
				place(p_board, tetramino, tetramino_pos, 'A' + tetramino_idx);
				if (solve_board(p_board, tetraminos, tetramino_idx + 1))
					return (1);
				place(p_board, tetramino, tetramino_pos, '.');
			}
		}
		tetramino_pos.x = -1;
	}
	return (0);
}

void			solve(const char **tetraminos,
				const int initial_board_size)
{
	t_board		board;
	int			i;

	i = -1;
	board.size = initial_board_size;
	board.cells = ft_strnew(board.size * board.size);
	ft_memset(board.cells, '.', board.size * board.size);
	while (!solve_board(&board, tetraminos, 0))
	{
		ft_strdel(&(board.cells));
		board.size++;
		board.cells = ft_strnew(board.size * board.size);
		ft_memset(board.cells, '.', board.size * board.size);
	}
	while (board.cells[++i])
	{
		if (i % board.size == 0 && i != 0)
			ft_putchar('\n');
		ft_putchar(board.cells[i]);
	}
	ft_putchar('\n');
	ft_strdel(&(board.cells));
}
