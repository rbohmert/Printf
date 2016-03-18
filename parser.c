/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:10:42 by rbohmert          #+#    #+#             */
/*   Updated: 2016/03/18 22:11:11 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	isformat(char c)
{
	return((c == 'd' || c == 'i' || c == 'u' || c == 'o'|| c == 'f' || c == 'e' || c == 'x' || c == 'X' || c == 'a'|| c == 'c' || c == 's' || c =='p' || c == 'n') ? 1 : 0);
}

int	get_arg(t_list **list, int i, char *str)
{
	t_arg	*arg;
	int	j;
	char	width[15];
	char	prec[15];
	int	k;
	
	j = i;
	init_arg(&arg, i);
	ft_bzero(width, 15);
	ft_bzero(prec, 15);
	while (!(isformat(str[j++])))
	{
		k = 0;
		if (str[j] == '-' || str[j] == '+' || str[j] == ' ' || str[j] == '0' || str[j] == '#')
			arg->flag = str[j];
		if ((str[j] >= '1' && str[j] <= '9') || str[j] == '*')
		{
			if (str[j] == '*')
			{
				arg->width = -1;
				j++;
			}
			else
			{
				while (str[j] >= '1' && str[j] <= '9')
				{
					width[k] = str[j];
					k++;
					j++;
				}
				arg->width = ft_atoi(width);
			}
		}
		if (str[j] == '.')
		{
			j++;
			k = (k == 0) ? k : 0;
			if (str[j] == '*')
			{
				arg->prec = -1;
				j++;
			}
			else
			{
				while ((str[j] >= '1' && str[j] <= '9'))
				{
					prec[k] = str[j];
					k++;
					j++;
				}
				arg->prec = ft_atoi(prec);
			}
		}
		if (ft_strncmp(&str[j], "ll", 2) == 0 || ft_strncmp(&str[j], "hh", 2) == 0)
		{
			arg->modif = (ft_strncmp(&str[j], "ll", 2)) ? 'H' : 'L';
			j++;
		}
		else if (str[j] == 'l' || str[j] == 'h' || str[j] == 'j' || str[j] == 'z')
			arg->modif = str[j];
	}
	arg->format = str[j - 1];
	ft_push_back(list, arg, 0);
	return (j - i);
}
	
void	parsing(char *str, t_list **list)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			i += get_arg(list, i, str);
		i++;
	}
}
