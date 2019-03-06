/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:48:22 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/06 18:48:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_ls.h"

void	fill_padding_max_values(t_l *file, int *max, int *tmp)
{
	if (max[0] < (*tmp = ft_nbrlen(file->symlink)))
		max[0] = *tmp;
	if (max[1] < (*tmp = ft_strlen(file->owner)))
		max[1] = *tmp;
	if (max[2] < (*tmp = ft_strlen(file->group)))
		max[2] = *tmp;
	if (max[3] < (*tmp = ft_strlen(file->size)))
		max[3] = *tmp;
}

void	fill_padding_file(t_l *file, int *max)
{
	file->padding[0] = max[0] - ft_nbrlen(file->symlink)
					- ft_strlen(file->extacl) + 2;
	file->padding[1] = max[1] - ft_strlen(file->owner) + 2;
	file->padding[2] = (max[2] - ft_strlen(file->group))
					+ (max[3] - ft_strlen(file->size)) + 2;
}

/*
**	Fill the padding in each t_l in arg
*/

void	fill_padding(t_list *files, int skipfolders)
{
	t_l		*file;
	t_list	*head;
	int		max[4];
	int		tmp;

	ft_bzero(max, sizeof(int) * 4);
	head = files;
	while (files)
	{
		file = files->content;
		if (!skipfolders || file->type == 0)
		{
			fill_padding_max_values(file, max, &tmp);
		}
		files = files->next;
	}
	files = head;
	while (files)
	{
		file = files->content;
		fill_padding_file(file, max);
		files = files->next;
	}
}
