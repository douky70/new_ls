/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:08:02 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/09 21:10:07 by akeiflin         ###   ########.fr       */
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
