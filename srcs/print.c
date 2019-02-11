/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:32:08 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/11 19:42:02 by akeiflin         ###   ########.fr       */
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
			ft_print_one(file);
		files = files->next;
	}
}

/*
**	Printing a dir without -R
*/

void	print_arg_dir(t_list *files)
{
	t_l	*file;
	int	i;

	i = 0;
	if (((t_l *)files->content)->type == 1 && ft_lstlen(files) == 1)
	{
		file = files->content;
		(check_arg('l')) ? printblock(file->sfiles) : 0;
		print_files(file->sfiles);
		return ;
	}
	while (files)
	{
		file = files->content;
		if (file->type == 1)
		{
			(i != 0) ? ft_putchar('\n') : 0;
			ft_putstr(file->name);
			ft_putendl(":");
			(check_arg('l')) ? printblock(file->sfiles) : 0;
			print_files(file->sfiles);
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
	if (check_arg('l'))
		full_file(file);
	else
		ft_putendl(parse_name(file->name));
}

/*
**	display a file line with -l
*/

void	full_file(t_l *file)
{
	char	*str;
	char	*to_free;
	str = NULL;
	str = ft_strljoin(str, file->acl, FIRST);
	str = ft_strljoin(str, file->extacl, FIRST);
	str = ft_strljoin(str, "\t", FIRST);
	str = ft_strljoin(str, ft_itoa(file->symlink), FIRST);
	str = ft_strljoin(str, "\t", FIRST);
	str = ft_strljoin(str, file->owner, FIRST);
	str = ft_strljoin(str, "\t", FIRST);
	str = ft_strljoin(str, file->group, FIRST);
	str = ft_strljoin(str, "\t", FIRST);
	str = ft_strljoin(str, ft_itoa(file->size), FIRST);
	str = ft_strljoin(str, "\t", FIRST);
	to_free = ft_lasttime(file->date);
	str = ft_strljoin(str, to_free, FIRST);
	free(to_free);
	str = ft_strljoin(str, "\t", FIRST);
	str = ft_strljoin(str, parse_name(file->name), FIRST);
	ft_putendl(str);
}

/*
**	computiong and displaing the count of block on the folder
*/

void		printblock(t_list *files)
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
