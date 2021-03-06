/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:27:44 by rbohmert          #+#    #+#             */
/*   Updated: 2016/06/12 18:34:38 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_minu(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] > 64 && s[i] < 91)
			s[i] += 32;
		i++;
	}
	return (s);
}
