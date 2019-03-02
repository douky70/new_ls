/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:08:19 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 16:47:56 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** Sort a list filled whit t_l by last modified time asc
*/

void	ft_t_l_sort_time(t_list *lst)
{
	t_l			*tmp;
	t_list		*head;
	int			change;

	if (!lst)
		return ;
	head = lst;
	change = 1;
	while (change && !(change = 0))
	{
		while (lst->next)
		{
			if (((t_l *)lst->content)->date < ((t_l *)lst->next->content)->date)
			{
				change = 1;
				tmp = lst->content;
				lst->content = lst->next->content;
				lst->next->content = tmp;
			}
			lst = lst->next;
		}
		lst = head;
	}
}

/*
** Sort a list filled whit t_l by last modified time desc
*/

void	ft_t_l_sort_time_r(t_list *lst)
{
	char		*tmp;
	t_list		*head;
	int			change;

	if (!lst)
		return ;
	head = lst;
	change = 1;
	while (change && !(change = 0))
	{
		while (lst->next)
		{
			if (((t_l *)lst->content)->date > ((t_l *)lst->next->content)->date)
			{
				change = 1;
				tmp = lst->content;
				lst->content = lst->next->content;
				lst->next->content = tmp;
			}
			lst = lst->next;
		}
		lst = head;
	}
}

/*
** Sort a list filled whit t_l by name
*/

void	ft_t_l_sort_r(t_list *lst)
{
	char		*tmp;
	t_list		*head;
	int			change;

	if (!lst)
		return ;
	head = lst;
	change = 1;
	while (change && !(change = 0))
	{
		while (lst->next)
		{
			if (ft_strcmp(((t_l *)lst->content)->name,
				((t_l *)lst->next->content)->name) < 0)
			{
				change = 1;
				tmp = lst->content;
				lst->content = lst->next->content;
				lst->next->content = tmp;
			}
			lst = lst->next;
		}
		lst = head;
	}
}

/*
** Sort a list filled whit t_l by name
*/

void	ft_t_l_sort(t_list *lst)
{
	char		*tmp;
	t_list		*head;
	int			change;

	if (!lst)
		return ;
	head = lst;
	change = 1;
	while (change && !(change = 0))
	{
		while (lst->next)
		{
			if (ft_strcmp(((t_l *)lst->content)->name,
				((t_l *)lst->next->content)->name) > 0)
			{
				change = 1;
				tmp = lst->content;
				lst->content = lst->next->content;
				lst->next->content = tmp;
			}
			lst = lst->next;
		}
		lst = head;
	}
}

/*
**	Sort ASC with t_l->type
*/

void	ft_sort_type(t_list *lst)
{
	char		*tmp;
	t_list		*head;
	int			change;

	if (!lst)
		return ;
	head = lst;
	change = 1;
	while (change && !(change = 0))
	{
		while (lst->next)
		{
			if ((((t_l *)lst->content)->type >= 0)
					&& (((t_l *)lst->next->content)->type) < 0)
			{
				change = 1;
				tmp = lst->content;
				lst->content = lst->next->content;
				lst->next->content = tmp;
			}
			lst = lst->next;
		}
		lst = head;
	}
}
