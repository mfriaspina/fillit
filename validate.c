/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esantaca <esantaca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 12:40:24 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/24 12:54:32 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	**get_tetra(int fd)
{
	char	*line;
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = (char **)ft_memalloc(sizeof(char*) * 27);
	line = ft_strnew(0);
	str[0] = ft_strnew(16);
	while (get_next_line(fd, &line))
	{
		if (line[0] == '\0')
			str[++i] = ft_strnew(16);
		else
		{
			j = -1;
			while (line[++j])
				if ((line[j] != '.' && line[j] != '#') || ft_strlen(line) != 4)
					return (NULL);
			str[i] = ft_strjoin(str[i], line);
		}
	}
	str[++i] = ft_strnew(1);
	ft_memdel((void **)&str[i]);
	return (str);
}

static int	check_tetra(char **str, int j)
{
	int i;
	int touch;

	while (str[++j])
	{
		i = -1;
		touch = 0;
		while (str[j][++i])
			if (str[j][i] == '#')
			{
				if (str[j][i - 1] == '#' && i % 4 != 0)
					touch++;
				if (str[j][i + 1] == '#' && i % 4 != 3)
					touch++;
				if (str[j][i + 4] == '#' && i + 4 <= 16)
					touch++;
				if (str[j][i - 4] == '#' && i - 4 >= 0)
					touch++;
			}
		if ((touch != 6 && touch != 8) || ft_strlen(str[j]) != 16)
			return (1);
	}
	return (0);
}

static char	**simplify(char **tetra)
{
	int i;
	int j;
	int num;

	i = -1;
	while (tetra[++i])
	{
		tetra[i] = ft_replace(tetra[i], 'A' + i, '#');
		j = -1;
		num = 0;
		while (tetra[i][++j])
			if (tetra[i][j] != '.')
				num++;
		if (num != 4)
			return (NULL);
	}
	return (tetra);
}

static char	**align(char **tetra, int i)
{
	int		j;
	int		k;

	while (tetra[++i])
	{
		while (!(ft_strncmp("....", tetra[i], 4)))
		{
			ft_memmove(tetra[i], &tetra[i][4], 4);
			ft_memmove(&tetra[i][4], &tetra[i][8], 4);
			ft_memmove(&tetra[i][8], &tetra[i][12], 4);
			ft_memmove(&tetra[i][12], "....", 4);
		}
		while (tetra[i][0] == '.' && tetra[i][4] == '.' && tetra[i][8] == '.')
		{
			j = -4;
			while ((j += 4) <= 12)
			{
				k = -1;
				while (++k < 4)
					tetra[i][k + j] = tetra[i][k + j + 1];
			}
		}
	}
	return (tetra);
}

char		**validate(int argc, int fd)
{
	char **str;

	if (argc != 2)
	{
		ft_putendl("usage: ./fillit source_file");
		return (NULL);
	}
	if (!(str = get_tetra(fd)))
	{
		ft_putendl("error");
		return (NULL);
	}
	if (check_tetra(str, -1) || !(str = simplify(str)))
	{
		ft_putendl("error");
		return (NULL);
	}
	str = align(str, -1);
	return (str);
}
