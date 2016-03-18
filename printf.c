/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:30:32 by rbohmert          #+#    #+#             */
/*   Updated: 2016/03/18 22:30:33 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	init_arg(t_arg **arg, int i)
{
	if (!(*arg = (t_arg *)malloc(sizeof(t_arg))))
		exit (2);
	(*arg)->width = 0;
	(*arg)->prec = 0;
	(*arg)->place = i;
	(*arg)->arg_num = 0;
	(*arg)->result = NULL;
	(*arg)->flag = 0;
	(*arg)->format = 0;
	(*arg)->modif = 0;
}

int		ft_printf(char *str, ...)
{
	t_list	*list;
	t_list	*tmp;
	va_list	ap;

	va_start(ap, str);
	list = NULL;
	parsing(str, &list);
	tmp = list;
	while (tmp)
	{
		if (((t_arg *)(tmp->content))->width == -1)
			((t_arg *)(tmp->content))->width = va_arg(ap, int);
		if (((t_arg *)(tmp->content))->prec == -1)
			((t_arg *)(tmp->content))->prec = va_arg(ap, int);
		if (((t_arg *)(tmp->content))->format == 's' || ((t_arg *)(tmp->content))->format == 'S')
			((t_arg *)(tmp->content))->arg_str = va_arg(ap, char *);
		else 
			((t_arg *)(tmp->content))->arg_num = va_arg(ap, int);
		tmp = tmp->next;
	} 
	/*while (list)
	{
		printf("wi:%d pre:%d pl:%d num:%d fla:%c for:%c mod:%c\n", ((t_arg *)list->content)->width, ((t_arg *)list->content)->prec, ((t_arg *)list->content)->place, ((t_arg *)list->content)->arg_num, ((t_arg *)list->content)->flag, ((t_arg *)list->content)->format, ((t_arg *)list->content)->modif);
		list = list->next;
	}*/
	va_end(ap);
	return (0);
}

int main ()
{
	ft_printf("dsc%#*llc vfe %12ihdsi %d hvuf %-.*c cd  dc % lf", 100, 43, 35, 999, 43, 0, 1010);
	return 0;
}
