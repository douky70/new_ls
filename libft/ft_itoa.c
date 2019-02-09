/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 08:43:40 by akeiflin          #+#    #+#             */
/*   Updated: 2018/11/16 01:06:24 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	int		numlen;
	int		positive;
	char	*str;
	long	num;

	numlen = ft_numlen(n);
	positive = ft_ispositive(n);
	if (!positive)
		numlen++;
	if (!(str = ft_strnew(numlen)))
		return (NULL);
	if (!positive)
		str[0] = '-';
	num = ft_abs(n);
	while ((!positive) ? numlen - 1 : numlen)
	{
		str[--numlen] = '0' + num % 10;
		num /= 10;
	}
	return (str);
}
