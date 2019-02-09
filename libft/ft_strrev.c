/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:12:25 by akeiflin          #+#    #+#             */
/*   Updated: 2019/01/31 17:48:23 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

/*
**	Return a new reversed string
*/

char	*ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	while (--len != 0)
	{
		res[i] = str[len];
		i++;
	}
	res[i++] = str[len];
	res[i] = '\0';
	return (res);
}
