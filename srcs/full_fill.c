/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:58:30 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/11 19:44:36 by akeiflin         ###   ########.fr       */
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
	struct passwd *pwd;

	pwd = getpwuid(st_uid);
	return (pwd->pw_name);
}

char		*ft_group(gid_t st_gid)
{
	struct group *gr;

	gr = getgrgid(st_gid);
	return (gr->gr_name);
}

//A FREE
// Mauvaise size d'alloc ATTENTION

char		*ft_perm(mode_t st_mode)
{
	char	*str;

	str = malloc(sizeof(str) * 11);
	*(str++) = ((S_ISDIR(st_mode)) ? 'd' : '-');
	*(str++) = ((st_mode & S_IRUSR) ? 'r' : '-');
	*(str++) = ((st_mode & S_IWUSR) ? 'w' : '-');
	*(str++) = ((st_mode & S_IXUSR) ? 'x' : '-');
	*(str++) = ((st_mode & S_IRGRP) ? 'r' : '-');
	*(str++) = ((st_mode & S_IWGRP) ? 'w' : '-');
	*(str++) = ((st_mode & S_IXGRP) ? 'x' : '-');
	*(str++) = ((st_mode & S_IROTH) ? 'r' : '-');
	*(str++) = ((st_mode & S_IWOTH) ? 'w' : '-');
	*(str) = ((st_mode & S_IXOTH) ? 'x' : '-');
	return (str - 9);
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
