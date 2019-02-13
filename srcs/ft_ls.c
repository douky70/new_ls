/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:45:58 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/13 22:32:13 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ls.h"

char	*g_arglist;

void	fill_one(t_l *file, struct stat buff)
{
	char	*symlinkname;

	if (check_arg('l'))
	{
		nff1(file, ft_perm(buff.st_mode), ft_extattr(file->name),
			buff.st_nlink);
		nff2(file, ft_owner(buff.st_uid), ft_group(buff.st_gid),
			buff.st_size);
		nff3(file, buff.st_mtimespec.tv_sec, buff.st_blocks,
			S_ISDIR(buff.st_mode));
		if (S_ISLNK(buff.st_mode))
		{
			if (!(symlinkname = malloc(buff.st_size + 1)))
				exit(1);
			readlink(file->name, symlinkname, buff.st_size + 1);
			symlinkname[buff.st_size] = '\0';;
			file->symlinkname = symlinkname;
		}
	}
	else
	{
		nff1(file, NULL, 0, 0);
		nff2(file, NULL, NULL, 0);
		nff3(file, buff.st_mtimespec.tv_sec, 0, S_ISDIR(buff.st_mode));
	}
}

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
			newfile->name = ft_strjoin(directory->name, "/");
			newfile->name = ft_strljoin(newfile->name, tmpdir->d_name, FIRST);
			subfiles = ft_lstaddnew(&subfiles, newfile, sizeof(t_l));
			free(newfile);
		}
	}
	closedir(dir);
	fill(subfiles);
	sort_files(subfiles);
	directory->sfiles = subfiles;
}

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
		if (file->acl)
			free(file->acl);
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

//	TODO
//	* Recursivity
//	* Symbolic link ERROR N LSTAT
//	* finish -l
//	* * finish acl
//	* * padding
//	* VERIFIER MALLOC PROTECTION
