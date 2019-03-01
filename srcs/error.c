/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:51:36 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/01 08:15:48 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "ft_ls.h"
#include "libft.h"

/*
**	Display the option error and exit
*/

void	ft_wrong_option(void)
{
	ft_putstr_fd("ft_ls: illegal option\nusage: ./ft_ls [-lRrat] [file ...]\n",
	2);
	exit(1);
}

/*
**	Display an error for a t_l
*/

void	print_err(t_l *file)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(parse_name(file->name), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
