/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:51:36 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/09 18:24:31 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "ft_ls.h"
#include "libft.h"

void	ft_wrong_option(void)
{
	ft_putstr_fd("ft_ls: illegal option\nusage: ./ft_ls [-lRrat] [file ...]\n",
	2);
	exit(1);
}

void	print_err(t_l *file)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
