/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 20:28:16 by rbohmert          #+#    #+#             */
/*   Updated: 2016/10/21 20:03:49 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long nbr, int base)
{
	char base_digits[16] = "0123456789ABCDEF";
	int converted_number[64];
	int i;
	long long n;
	char *result;

	i = 0;
	n = nbr;
	nbr = (nbr < 0) ? nbr * -1 : nbr;
	while (nbr != 0 || i == 0)
	{
		converted_number[i] = nbr % base;
		nbr = nbr / base;
		i++;
	}
	if (!(result = (char *)malloc(--i + 2)))
		return (NULL);
	ft_bzero(result, i + 2);
	result[0] = (n < 0) ? '-' : 0;
	n = n < 0 ? 1 : 0;
	while (i >= 0)
		result[n++] = base_digits[converted_number[i--]];
	
	return (result);
}
