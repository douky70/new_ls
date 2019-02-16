/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:58:30 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/15 12:16:48 by akeiflin         ###   ########.fr       */
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

//A FREE

char		*ft_lasttime(time_t filetime)
{
	char		*str;
	time_t		mytime;
	char		*texttime;
	int			len;

	texttime = ctime(&filetime);
	time(&mytime);
	if (mytime - filetime < 15724800)
	{
		str = ft_strdup(texttime + 4);
		str[12] = 0;
	}
	else
	{
		str = ft_strdup(texttime + 4);
		len = ft_strlen(str);
		str[12] = ' ';
		str[13] = str[len - 5];
		str[14] = str[len - 4];
		str[15] = str[len - 3];
		str[16] = str[len - 2];
		str[17] = 0;
	}
	return (str);
}

char		*ft_owner(uid_t st_uid)
{
	struct passwd	*pwd;
	char			*id;

	pwd = getpwuid(st_uid);
	if (pwd)
		id = pwd->pw_name;
	else
		id = ft_itoa(st_uid);
	return (id);
}

char		*ft_group(gid_t st_gid)
{
	struct group	*gr;
	char			*id;

	gr = getgrgid(st_gid);
	if (gr)
		id = gr->gr_name;
	else
		id = ft_itoa(st_gid);
	return (gr->gr_name);
}

//A FREE
// Mauvaise size d'alloc ATTENTION

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

char		*ft_perm(mode_t st_mode)
{
	char	*str;

	str = NULL;
	str = ft_set_type(st_mode);
	str = ft_strljoin(str, ((st_mode & S_IRUSR) ? "r" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IWUSR) ? "w" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IXUSR) ? "x" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IRGRP) ? "r" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IWGRP) ? "w" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IXGRP) ? "x" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IROTH) ? "r" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IWOTH) ? "w" : "-"), FIRST);
	str = ft_strljoin(str, ((st_mode & S_IXOTH) ? "x" : "-"), FIRST);
	return (str);
}

// A refaire et comprendre

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
