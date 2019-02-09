/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:17:14 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/09 21:39:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

char	*g_arglist;

/*
** Take the param's and parse when they start by "-"
** Return: Param list on a char * or "" if no param found
*/

char	*ft_parse_arg(int argc, char **argv)
{
	int		i;
	char	*arg;

	i = 0;
	arg = NULL;
	while (++i < argc)
		if (!(ft_strlen(argv[i]) > 1 && argv[i][0] == '-'))
			break ;
		else
			arg = ft_strfjoin(arg, ft_strdup(argv[i] + 1));
	i = -1;
	while (arg && arg[++i])
	{
		if (!ft_strchr(AVAILABLE_ARG, arg[i]))
			ft_wrong_option();
	}
	if (arg == NULL)
		arg = "";
	return (arg);
}

/*
** Take the param's and parse the files and folder list
** Return: Param list on a t_list * malloced with t_l only name filled
*/

t_list	*ft_arg_file(int argc, char **argv)
{
	int		i;
	t_list	*lst;
	t_l		*file;

	lst = NULL;
	i = 0;
	while (++i < argc)
		if (!(ft_strlen(argv[i]) > 1 && argv[i][0] == '-'))
			break ;
	i--;
	while (++i < argc)
	{
		file = malloc(sizeof(t_l));
		file->name = argv[i];
		lst = ft_lstappendnew(&lst, file, sizeof(t_l));
	}
	if (lst == NULL)
	{
		file = malloc(sizeof(t_l));
		file->name = ft_strdup(".");
		lst = ft_lstappendnew(&lst, file, sizeof(t_l));
	}
	return (lst);
}

/*
** Return 1 if the arg is gived to the binary,
** meanwile return 0
*/

int		check_arg(char c)
{
	if (ft_strchr(g_arglist, c) == NULL)
		return (0);
	else
		return (1);
}
