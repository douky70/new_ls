/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:08:02 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/20 16:27:01 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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
		if (res[i] == '/' && res[i + 1] != '/')
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

char	*first_parse_name(char *name)
{
	char		*rev;
	char		*res;
	long long	i;

	i = 0;
	if (ft_strcmp(name, "/") == 0)
		return (ft_strdup("/"));
	rev = ft_strrev(name);
	while (rev[i] == '/')
		i++;
	res = ft_strrev(&(rev[i]));
	free(rev);
	return (res);
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
