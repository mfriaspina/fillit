/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:28:54 by mfrias            #+#    #+#             */
/*   Updated: 2019/05/05 13:30:42 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_result(int size, int original, int n, char *res)
{
	while (size >= 0)
	{
		if (original > 0)
			res[size--] = '0' + original % 10;
		else
			res[size--] = '0' + (original % 10) * -1;
		original = original / 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

char		*ft_itoa(int n)
{
	int		size;
	int		original;
	char	*res;

	size = 0;
	original = n;
	if (n < 0)
		size++;
	while (n <= -10 || n >= 10)
	{
		n = n / 10;
		size++;
	}
	res = ft_strnew(size + 1);
	if (!res)
		return (NULL);
	return (ft_result(size, original, n, res));
}
