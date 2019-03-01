/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:04:08 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/01 08:12:41 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Fill a t_l
*/

void	nff1(t_l *file, char *acl, char *extacl, int symlink)
{
	file->acl = acl;
	file->extacl = extacl;
	file->symlink = symlink;
}

/*
** Fill a t_l
*/

void	nff2(t_l *file, char *owner, char *group, char *size)
{
	file->owner = owner;
	file->group = group;
	file->size = size;
}

/*
** Fill a t_l
*/

void	nff3(t_l *file, time_t date, int block, int type)
{
	file->date = date;
	file->block = block;
	file->type = type;
}
