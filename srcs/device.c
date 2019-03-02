/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:54:15 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 16:58:51 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include "ft_ls.h"

/*
**	fill the padding between the major and the minor
**	Return a malloced string filled with space
*/

char	*add_device_padding(int nbr, int majmin)
{
	int		nb;
	char	*res;

	if (majmin == 0)
		nb = 3;
	else
		nb = 4;
	nb -= ft_nbrlen(nbr);
	res = ft_strnew(nb);
	while (--nb >= 0)
		res[nb] = ' ';
	return (res);
}

/*
**	Fill the minor & major
**	Return a malloced string with major and minor
*/

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
	res = ft_strljoin(res, add_device_padding(major, 0), SECOND);
	res = ft_strljoin(res, ft_itoa(major), BOTH);
	res = ft_strljoin(res, ",", FIRST);
	res = ft_strljoin(res, add_device_padding(minor, 1), BOTH);
	res = ft_strljoin(res, ft_itoa(minor), BOTH);
	return (res);
}
