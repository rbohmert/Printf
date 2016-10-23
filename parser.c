/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:10:42 by rbohmert          #+#    #+#             */
/*   Updated: 2016/06/12 16:50:40 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	isformat(char c)
{
	return((c == '%' || c == 'd' || c == 'D' || c == 'O' || c == 'U' || c == 'i' || c == 'u' || c == 'o'|| c == 'f' || c == 'e' || c == 'x' || c == 'X' || c == 'a'|| c == 'c' || c == 's' || c =='p' || c == 'n') ? 1 : 0);
}

int	get_arg(t_list **list, int i, char *str)
{
	t_arg	*arg;
	int	j;
	char	width[15];
	char	prec[15];
	int	k;
	
	j = i + 1;
	init_arg(&arg, i);
	ft_bzero(width, 15);
	ft_bzero(prec, 15);
	while (!(isformat(str[j])))
	{
		k = 0;
		if (str[j] == '#')
			arg->flag_hash = '#';
		if (str[j] == '0' || str[j] == '-')
			arg->flag_pad = str[j];
		if (str[j] == ' ' || str[j] == '+')
			arg->flag_add = str[j];
		if ((str[j] >= '1' && str[j] <= '9') || str[j] == '*')
		{
			if (str[j] == '*')
			{
				arg->width = -1;
				j++;
			}
			else
			{
				while (str[j] >= '0' && str[j] <= '9')
					width[k++] = str[j++];
				arg->width = ft_atoi(width);
				j--;
			}
		}
		if (str[j] == '.')
		{
			j++;
			if (str[j] == '*')
			{
				arg->prec = -1;
				j++;
			}
			else
			{
				while ((str[j] >= '0' && str[j] <= '9'))
					prec[k++] = str[j++];
				arg->prec = ft_atoi(prec);
				j--;
			}
		}
		if (ft_strncmp(&str[j], "ll", 2) == 0 || ft_strncmp(&str[j], "hh", 2) == 0)
			arg->modif = (ft_strncmp(&str[j++], "ll", 2)) ? 'H' : 'L';
		else if (str[j] == 'l' || str[j] == 'h' || str[j] == 'j' || str[j] == 'z')
			arg->modif = str[j];
		j++;
	}
	arg->format = str[j];
	ft_push_back(list, arg, 0);
	return (j - i);
}
	
int		parsing(char *str, t_list **list)
{
	int i;
	int nbchar;

	i = 0;
	nbchar = 0;
	while (str[i])
	{
		if (str[i] == '%')
			i += get_arg(list, i, str);
		else
			nbchar++;
		i++;
	}
	return (nbchar);
}
