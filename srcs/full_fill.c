/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:58:30 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/05 17:17:49 by akeiflin         ###   ########.fr       */
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

char		*ft_lasttime_sub(char *res, char **str, int spe)
{
	if (ft_strlen(str[2]) == 1)
		res = ft_strljoin(res, "  ", NONE);
	else
		res = ft_strljoin(res, " ", NONE);
	res = ft_strljoin(res, str[2], BOTH);
	res = ft_strljoin(res, " ", FIRST);
	res = ft_strljoin(res, str[1], BOTH);
	res = ft_strljoin(res, ((spe == 4) ? "   " : "  "), FIRST);
	res = ft_strljoin(res, str[spe], BOTH);
	free(str[0]);
	free(str[((spe == 4) ? 3 : 4)]);
	free(str[5]);
	free(str);
	return (res);
}

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
		res = ft_lasttime_sub(res, str, 4);
		return (res);
	}
	else
	{
		str[3][5] = '\0';
		res = ft_lasttime_sub(res, str, 3);
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
