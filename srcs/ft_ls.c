/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:45:58 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/06 18:53:21 by akeiflin         ###   ########.fr       */
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
