/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:32:08 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/06 18:52:40 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

void	print_arg_dir_print(t_l *file)
{
	(check_arg('l') && file->sfiles) ? printblock(file->sfiles) : 0;
	print_files(file->sfiles);
	(check_arg('R')) ? sub_folder_search_r(file->sfiles) : 0;
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
		print_arg_dir_print(file);
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
			print_arg_dir_print(file);
		}
		++i;
		files = files->next;
	}
}

/*
**	print i spaces
*/

void	put_space(int i)
{
	while (--i >= 0)
		ft_putchar(' ');
}

void	full_file_norm(t_l *file)
{
	char	*to_free;

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
	full_file_norm(file);
}
