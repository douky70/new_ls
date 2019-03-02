/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:45:58 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 17:35:14 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ls.h"

char	*g_arglist;

/*
**	Free all my files
*/

void	free_files(t_list *files)
{
	t_list	*next;
	t_l		*file;

	while (files)
	{
		next = files->next;
		file = files->content;
		if (file->type == 1 && file->sfiles)
			free_files(file->sfiles);
		free(file->name);
		if (file->symlinkname)
			free(file->symlinkname);
		if (check_arg('l'))
		{
			free(file->acl);
			free(file->owner);
			free(file->group);
			free(file->size);
		}
		free(file);
		free(files);
		files = next;
	}
}

void	fill_padding_sub(t_l *file, int *max, int *tmp)
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

void	fill_padding_sub2(t_l *file, int *max)
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
			fill_padding_sub(file, max, &tmp);
		}
		files = files->next;
	}
	files = head;
	while (files)
	{
		file = files->content;
		fill_padding_sub2(file, max);
		files = files->next;
	}
}

int		main(int argc, char **argv)
{
	t_list	*files;
	t_list	*head;

	g_arglist = ft_parse_arg(argc, argv);
	files = ft_arg_file(argc, argv);
	ft_t_l_sort(files);
	fill(files);
	(check_arg('l')) ? fill_padding(files, 1) : 0;
	sort_files(files);
	head = files;
	while (files)
	{
		if (((t_l *)files->content)->type == 1)
			fill_dir(files->content);
		files = files->next;
	}
	files = head;
	print_arg_files(files);
	print_arg_dir(files);
	free_files(files);
	return (0);
}
