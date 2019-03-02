/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:50:45 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 17:33:01 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

void	symlinkfill(t_l *file, t_stat buff)
{
	char	*symlinkname;

	if (S_ISLNK(buff.st_mode))
	{
		if (buff.st_size == 0)
			buff.st_size = MAXNAMLEN;
		if (!(symlinkname = malloc(buff.st_size + 1)))
			exit(1);
		readlink(file->name, symlinkname, buff.st_size + 1);
		symlinkname[buff.st_size] = '\0';
		file->symlinkname = symlinkname;
	}
}

/*
**	Full fill one t_l
*/

void	fill_one(t_l *file, t_stat buff)
{
	char	*size;
	int		dir;

	dir = is_dir(buff, file);
	if (check_arg('l'))
	{
		if (S_ISBLK(buff.st_mode) || S_ISCHR(buff.st_mode))
			size = device(buff.st_rdev);
		else
			size = ft_itoa(buff.st_size);
		nff(file, ft_perm(buff.st_mode), ft_extattr(file->name), buff.st_nlink);
		nff2(file, ft_owner(buff.st_uid), ft_group(buff.st_gid), size);
		nff3(file, buff.st_mtimespec.tv_sec, buff.st_blocks, dir);
		symlinkfill(file, buff);
	}
	else
	{
		nff(file, NULL, 0, 0);
		nff2(file, NULL, NULL, 0);
		nff3(file, buff.st_mtimespec.tv_sec, 0, dir);
	}
}

void	fill_dir_sub(t_l *directory, t_list *subfiles)
{
	fill(subfiles);
	(check_arg('l')) ? fill_padding(subfiles, 0) : 0;
	sort_files(subfiles);
	directory->sfiles = subfiles;
}

/*
**	Read ad fill a DIR
*/

void	fill_dir(t_l *directory)
{
	DIR				*dir;
	struct dirent	*tmpdir;
	t_list			*subfiles;
	t_l				*newfile;

	subfiles = NULL;
	if (!(dir = opendir(directory->name)))
		return (print_err(directory));
	while ((tmpdir = readdir(dir)))
	{
		if (check_arg('a') || tmpdir->d_name[0] != '.')
		{
			newfile = ft_calloc(sizeof(t_l));
			if (ft_strcmp(directory->name, "/") != 0)
				newfile->name = ft_strjoin(directory->name, "/");
			else
				newfile->name = ft_strdup("/");
			newfile->name = ft_strljoin(newfile->name, tmpdir->d_name, FIRST);
			subfiles = ft_lstaddnew(&subfiles, newfile, sizeof(t_l));
			(newfile) ? free(newfile) : 0;
		}
	}
	closedir(dir);
	fill_dir_sub(directory, subfiles);
}

/*
**	Fill a t_l list
*/

void	fill(t_list *files)
{
	struct stat	buff;
	t_l			*file;

	while (files)
	{
		file = files->content;
		if (lstat(file->name, &buff) == 0)
			fill_one(file, buff);
		else
		{
			print_err(file);
			file->error = -1;
			file->type = -1;
		}
		files = files->next;
	}
}
