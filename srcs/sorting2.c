/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:48:07 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 16:48:18 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
**	Sort the files matching with args
*/

void	sort_files(t_list *files)
{
	if (files)
	{
		if (check_arg('r'))
			ft_t_l_sort_r(files);
		else
			ft_t_l_sort(files);
		if (check_arg('t') && check_arg('r'))
			ft_t_l_sort_time_r(files);
		else if (check_arg('t'))
			ft_t_l_sort_time(files);
	}
}
