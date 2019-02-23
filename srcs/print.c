/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:32:08 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/23 17:24:14 by akeiflin         ###   ########.fr       */
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

void	r_param(t_l *file)
{
	fill_dir(file);
	ft_putchar('\n');
	ft_putstr(file->name);
	ft_putendl(":");
	(check_arg('l')) ? printblock(file->sfiles) : 0;
	print_files(file->sfiles);
	sub_folder_search_r(file->sfiles);
}

void	sub_folder_search_r(t_list *files)
{
	t_l	*file;

	while (files)
	{
		file = files->content;
		if (file->type == 1 && !file->symlinkname && ft_strcmp(parse_name(file->name), ".") != 0 && ft_strcmp(parse_name(file->name), "..") != 0)
			r_param(file);
		files = files->next;
	}
}

/*
**	Printing a dir without -R
*/

void	print_arg_dir(t_list *files)
{
	t_l			*file;
	static int	i = 0;

	if (((t_l *)files->content)->type == 1 && ft_lstlen(files) == 1)
	{
		file = files->content;
		(check_arg('l')) ? printblock(file->sfiles) : 0;
		print_files(file->sfiles);
		(check_arg('R')) ? sub_folder_search_r(file->sfiles) : 0;
		return ;
	}
	while (files)
	{
		file = files->content;
		if (file->type == 1)
		{
			if (i != 0)
				ft_putchar('\n');
			ft_putstr(file->name);
			ft_putendl(":");
			(check_arg('l')) ? printblock(file->sfiles) : 0;
			print_files(file->sfiles);
			(check_arg('R')) ? sub_folder_search_r(file->sfiles) : 0;
		}
		++i;
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

void	put_space(int i)
{
	while (--i >= 0)
		ft_putchar(' ');
}

/*
**	display a file line with -l
*/

void	full_file(t_l *file)
{
	char	*to_free;

	ft_putstr(file->acl);
	ft_putstr(file->extacl);
	put_space(file->padding[0]);
	to_free = ft_itoa(file->symlink);
	ft_putstr(to_free);
	free(to_free);
	put_space(1);
	ft_putstr(file->owner);
	put_space(file->padding[1]);
	ft_putstr(file->group);
	put_space(file->padding[2]);
	ft_putstr(file->size);
	to_free = ft_lasttime(file->date);
	ft_putstr(to_free);
	free(to_free);
	put_space(1);
	if (file->fullname == 0)
		ft_putstr(parse_name(file->name));
	else
		ft_putstr(file->name);
	if (file->symlinkname)
	{
		ft_putstr(" -> ");
		ft_putstr(file->symlinkname);
	}
	ft_putchar('\n');
}

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
