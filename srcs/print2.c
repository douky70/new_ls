/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:41:11 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 16:42:16 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

/*
**	For print only files passed in arg
*/

void	print_arg_files(t_list *files)
{
	t_l		*file;

	while (files)
	{
		file = files->content;
		if (file->error == 0 && file->type == 0)
		{
			file->fullname = 1;
			ft_print_one(file);
		}
		files = files->next;
	}
}

/*
**	Fill a folder and print it for finaly check for another su folder
*/

void	r_param(t_l *file)
{
	fill_dir(file);
	ft_putchar('\n');
	ft_putstr(file->name);
	ft_putendl(":");
	(check_arg('l') && file->sfiles) ? printblock(file->sfiles) : 0;
	print_files(file->sfiles);
	sub_folder_search_r(file->sfiles);
}

/*
**	Look for subfolder
*/

void	sub_folder_search_r(t_list *files)
{
	t_l	*file;

	while (files)
	{
		file = files->content;
		if (file->type == 1 && !file->symlinkname
				&& ft_strcmp(parse_name(file->name), ".") != 0
				&& ft_strcmp(parse_name(file->name), "..") != 0)
			r_param(file);
		files = files->next;
	}
}

/*
**	Just print a t_list of file
*/

void	print_files(t_list *files)
{
	t_l		*file;

	while (files)
	{
		file = files->content;
		ft_print_one(file);
		files = files->next;
	}
}

/*
**	Controleur for -l option
*/

void	ft_print_one(t_l *file)
{
	if (file->error == 0)
	{
		if (check_arg('l'))
			full_file(file);
		else if (file->fullname == 0)
			ft_putendl(parse_name(file->name));
		else if (file->fullname == 1)
			ft_putendl(file->name);
	}
}
