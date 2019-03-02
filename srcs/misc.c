/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:08:02 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 17:36:16 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ls.h"

/*
**	Return a pointer on the beggin on the file name
*/

char	*parse_name(char *name)
{
	char	*res;
	size_t	i;
	size_t	len;

	len = ft_strlen(name);
	if (name[0] == '/')
	{
		len--;
		name++;
	}
	i = 0;
	res = ft_strrev(name);
	while (res[i + 1])
	{
		if (res[i] == '/' && res[i + 1] != '\\')
			break ;
		i++;
	}
	if (i + 1 == len)
		i = 0;
	else
		i = len - i;
	free(res);
	return (&(name[i]));
}

int		ft_nbrlen(unsigned long long n)
{
	if (n == 0)
		return (1);
	else if (n / 10 > 0)
		return (1 + ft_nbrlen(n / 10));
	else
		return (1);
}

int		is_dir(t_stat buff, t_l *file)
{
	char	*symlinkname;
	t_stat	symbuff;

	symlinkname = NULL;
	if (S_ISLNK(buff.st_mode))
	{
		if (buff.st_size == 0)
			buff.st_size = MAXNAMLEN;
		if (!(symlinkname = malloc(buff.st_size + 1)))
			exit(1);
		readlink(file->name, symlinkname, buff.st_size + 1);
		symlinkname[buff.st_size] = '\0';
		stat(symlinkname, &symbuff);
		(symlinkname) ? free(symlinkname) : 0;
		return (S_ISDIR(symbuff.st_mode));
	}
	else
		return (S_ISDIR(buff.st_mode));
}
