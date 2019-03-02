/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:42:49 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 16:43:11 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
**	computiong and displaing the count of block on the folder
*/

void	printblock(t_list *files)
{
	int		total;
	t_l		*file;

	total = 0;
	while (files)
	{
		file = files->content;
		total += file->block;
		files = files->next;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}
