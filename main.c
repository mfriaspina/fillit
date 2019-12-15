/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esantaca <esantaca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:50:06 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/24 12:33:32 by esantaca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			main(int argc, char **argv)
{
	int		fd;
	char	**tetraminos;
	int		tetramino_count;
	int		initial_board_size;

	tetramino_count = 0;
	fd = open(argv[1], O_RDONLY);
	if (!(tetraminos = validate(argc, fd)))
		return (-1);
	while (tetraminos[tetramino_count])
		tetramino_count++;
	initial_board_size = ft_sqrt(tetramino_count * 4);
	if ((initial_board_size * initial_board_size) != (tetramino_count * 4))
		initial_board_size++;
	solve((const char**)tetraminos, initial_board_size);
	close(fd);
	ft_strdel(tetraminos);
	return (0);
}
