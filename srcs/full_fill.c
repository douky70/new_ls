/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:58:30 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/01 08:34:23 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include "libft.h"

/*
**	calc the last use date for a file with the time_t
**	Return a malloced string with the last use date
*/

char		*ft_lasttime(time_t filetime)
{
	char		**str;
	char		*res;
	time_t		mytime;
	char		*texttime;

	res = NULL;
	texttime = ctime(&filetime);
	time(&mytime);
	str = ft_strsplit(texttime, ' ');
	if (mytime - filetime > 15724800 || mytime < filetime)
	{
		str[4][4] = '\0';
		if (ft_strlen(str[2]) == 1)
			res = ft_strljoin(res, "  ", NONE);
		else
			res = ft_strljoin(res, " ", NONE);
		res = ft_strljoin(res, str[2], BOTH);
		res = ft_strljoin(res, " ", FIRST);
		res = ft_strljoin(res, str[1], BOTH);
		res = ft_strljoin(res, "  ", FIRST);
		res = ft_strljoin(res, str[4], BOTH);
		free(str[0]);
		free(str[3]);
		free(str[5]);
		free(str);
		return (res);
	}
	else
	{
		str[3][5] = '\0';
		if (ft_strlen(str[2]) == 1)
			res = ft_strljoin(res, "  ", NONE);
		else
			res = ft_strljoin(res, " ", NONE);
		res = ft_strljoin(res, str[2], BOTH);
		res = ft_strljoin(res, " ", FIRST);
		res = ft_strljoin(res, str[1], BOTH);
		res = ft_strljoin(res, " ", FIRST);
		res = ft_strljoin(res, str[3], BOTH);
		free(str[0]);
		free(str[4]);
		free(str[5]);
		free(str);
		return (res);
	}

	return (res);
}

/*
**	Return a malloced string with the owner name
*/

char		*ft_owner(uid_t st_uid)
{
	struct passwd	*pwd;
	char			*id;

	pwd = getpwuid(st_uid);
	if (pwd)
		id = ft_strdup(pwd->pw_name);
	else
		id = ft_itoa(st_uid);
	return (id);
}

/*
**	Return a malloced string with the group name
*/

char		*ft_group(gid_t st_gid)
{
	struct group	*gr;
	char			*id;

	gr = getgrgid(st_gid);
	if (gr)
		id = ft_strdup(gr->gr_name);
	else
		id = ft_itoa(st_gid);
	return (id);
}

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
**	Return a malloced string with the sticky bit on group
*/

char		*sticky_group(mode_t st_mode, char *str)
{
	if (st_mode & S_ISGID) // GRP sSx
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
**	Return a malloced string with the sticky bit on user
*/

char		*sticky_user(mode_t st_mode, char *str)
{
	if (st_mode & S_ISUID) // USER sSx
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
**	Return a malloced string with the sticky bit on other
*/

char		*sticky_other(mode_t st_mode, char *str)
{
	if (st_mode & S_ISVTX) // OTHER tTx
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

/*
**	Add the extented ACL
*/

char		*ft_extattr(char *name)
{
	ssize_t		xattr;
	acl_t		acl;
	acl_entry_t	dummy;

	acl = NULL;
	dummy = NULL;
	acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		return ("@");
	else if (acl != NULL)
		return ("+");
	else
		return (0);
}
