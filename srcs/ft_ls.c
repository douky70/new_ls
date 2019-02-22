/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:45:58 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/21 16:48:10 by akeiflin         ###   ########.fr       */
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
#include <sys/types.h>

char	*g_arglist;

char	*add_device_padding(int nbr)
{
	int		nb;
	char	*res;

	nb = 4 - ft_nbrlen(nbr);
	res = ft_strnew(nb);
	while  (--nb >= 0)
		res[nb] = ' ';
	return (res); // 1 de trop sur le major
}

char	*device(dev_t st_rdev)
{
	int		major;
	int		minor;
	char	*res;

	major = 0;
	minor = 0;
	major = major(st_rdev);
	minor = minor(st_rdev);
	res = NULL;
	res = ft_strljoin(res, add_device_padding(major), SECOND);
	res = ft_strljoin(res, ft_itoa(major), BOTH);
	res = ft_strljoin(res, ",", FIRST);
	res = ft_strljoin(res, add_device_padding(minor), BOTH);
	res = ft_strljoin(res, ft_itoa(minor), BOTH);
	return (res);
}

void	fill_one(t_l *file, struct stat buff)
{
	char	*symlinkname;
	char	*size;

	if (check_arg('l'))
	{
		if (!S_ISLNK(buff.st_mode) && !S_ISDIR(buff.st_mode) && !S_ISREG(buff.st_mode))
			size = device(buff.st_rdev);
		else
			size = ft_itoa(buff.st_size);
		nff1(file, ft_perm(buff.st_mode), ft_extattr(file->name),
			buff.st_nlink);
		nff2(file, ft_owner(buff.st_uid), ft_group(buff.st_gid),
			size);
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
			if (ft_strcmp(directory->name , "/") != 0)
				newfile->name = ft_strjoin(directory->name, "/");
			else
				newfile->name = ft_strdup("/");
			newfile->name = ft_strljoin(newfile->name, tmpdir->d_name, FIRST);
			subfiles = ft_lstaddnew(&subfiles, newfile, sizeof(t_l));
			free(newfile);
		}
	}
	closedir(dir);
	fill(subfiles);
	(check_arg('l')) ? fill_padding(subfiles, 0) : 0;
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

void	fill_padding(t_list *files, int skipfolders)
{
	t_l 	*file;
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
			(max[0] < (tmp = ft_nbrlen(file->symlink))) ? max[0] = tmp : 0;
			(max[1] < (tmp = ft_strlen(file->owner))) ? max[1] = tmp : 0;
			(max[2] < (tmp = ft_strlen(file->group))) ? max[2] = tmp : 0;
			(max[3] < (tmp = ft_strlen(file->size))) ? max[3] = tmp : 0;
		}
		files = files->next;
	}
	files = head;
	while (files)
	{
		file = files->content;
		file->padding[0] = max[0] - ft_nbrlen(file->symlink) - ft_strlen(file->extacl) + 2;
		file->padding[1] = max[1] - ft_strlen(file->owner) + 2;
		file->padding[2] = (max[2] - ft_strlen(file->group)) + (max[3] - ft_strlen(file->size)) + 2;
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

//	TODO
//	* Symbolic link ERROR N LSTAT (Si il existe pas)
//	* Dissplay symlink (/dev/stderr ????)
//	* date fr/en???
//	* VERIFIER MALLOC PROTECTION
//	* DIFF ls -t pas au point (Fichier cree en mm temps)
//	* majeur padding
