/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_fill2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:44:49 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 16:47:40 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"

/*
**	Return the first ACL caracter malloced
*/

char		*ft_set_type(mode_t st_mode)
{
	char	*str;

	str = NULL;
	if (S_ISDIR(st_mode))
		str = ft_strjoin(str, "d");
	else if (S_ISCHR(st_mode))
		str = ft_strjoin(str, "c");
	else if (S_ISBLK(st_mode))
		str = ft_strjoin(str, "b");
	else if (S_ISFIFO(st_mode))
		str = ft_strjoin(str, "p");
	else if (S_ISSOCK(st_mode))
		str = ft_strjoin(str, "s");
	else if (S_ISLNK(st_mode))
		str = ft_strjoin(str, "l");
	else
		str = ft_strjoin(str, "-");
	return (str);
}

/*
**	Return a malloced string with the sticky bit on group (sSx)
*/

char		*sticky_group(mode_t st_mode, char *str)
{
	if (st_mode & S_ISGID)
	{
		if (st_mode & S_IXGRP)
			str = ft_strljoin(str, "s", FIRST);
		else
			str = ft_strljoin(str, "S", FIRST);
	}
	else if (st_mode & S_IXGRP)
		str = ft_strljoin(str, "x", FIRST);
	else
		str = ft_strljoin(str, "-", FIRST);
	return (str);
}

/*
**	Return a malloced string with the sticky bit on user (sSx)
*/

char		*sticky_user(mode_t st_mode, char *str)
{
	if (st_mode & S_ISUID)
	{
		if (st_mode & S_IXUSR)
			str = ft_strljoin(str, "s", FIRST);
		else
			str = ft_strljoin(str, "S", FIRST);
	}
	else if (st_mode & S_IXUSR)
		str = ft_strljoin(str, "x", FIRST);
	else
		str = ft_strljoin(str, "-", FIRST);
	return (str);
}

/*
**	Return a malloced string with the sticky bit on other tTx
*/

char		*sticky_other(mode_t st_mode, char *str)
{
	if (st_mode & S_ISVTX)
	{
		if (st_mode & S_IXOTH)
			str = ft_strljoin(str, "t", FIRST);
		else
			str = ft_strljoin(str, "T", FIRST);
	}
	else if (st_mode & S_IXOTH)
		str = ft_strljoin(str, "x", FIRST);
	else
		str = ft_strljoin(str, "-", FIRST);
	return (str);
}

/*
**	Return the mallocde ACL
*/

char		*ft_perm(mode_t st_mode)
{
	char	*str;

	str = NULL;
	str = ft_set_type(st_mode);
	str = ft_strljoin(str, ((st_mode & S_IRUSR) ? "r" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IWUSR) ? "w" : "-"), FIRST);
	str = sticky_user(st_mode, str);
	str = ft_strljoin(str, ((st_mode & S_IRGRP) ? "r" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IWGRP) ? "w" : "-"), FIRST);
	str = sticky_group(st_mode, str);
	str = ft_strljoin(str, ((st_mode & S_IROTH) ? "r" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IWOTH) ? "w" : "-"), FIRST);
	str = sticky_other(st_mode, str);
	return (str);
}
