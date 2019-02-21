/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 08:42:21 by akeiflin          #+#    #+#             */
/*   Updated: 2019/02/20 12:05:31 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define AVAILABLE_ARG "lRart"

# include <sys/stat.h>
# include <stdbool.h>
# include <string.h>
# include "libft.h"

typedef struct	stat	t_stat;
typedef	struct	s_l
{
	char		*name;
	char		*symlinkname;
	t_list		*sfiles;
	char		*acl;
	char		*extacl;
	int			symlink;
	char		*owner;
	char		*group;
	long		size;
	time_t		date;
	int			block;
	int			error;
	int			type;
	int			padding[4];
}				t_l;

void			ft_wrong_option(void);
void			print_err(t_l *file);

char			*ft_parse_arg(int argc, char **argv);
t_list			*ft_arg_file(int argc, char **argv);
int				check_arg(char c);

void			fill_one(t_l *file,struct stat buff);
void			fill(t_list *files);
void			fill_dir(t_l *directory);
void			fill_padding(t_list *files, int skipfolders);
void			nff1(t_l *file, char *acl, char *extacl, int symlink);
void			nff2(t_l *file, char *owner, char *group, long size);
void			nff3(t_l *file, time_t date, int block, int type);

void			ft_t_l_sort_time(t_list *lst);
void			ft_t_l_sort_time_r(t_list *lst);
void			ft_t_l_sort_r(t_list *lst);
void			ft_t_l_sort(t_list *lst);
void			ft_sort_type(t_list *lst);
void			sort_files(t_list *files);

char			*ft_lasttime(time_t filetime);
char			*ft_owner(uid_t st_uid);
char			*ft_group(gid_t st_gid);
char			*ft_perm(mode_t st_mode);
char			*ft_extattr(char *name);

void			print_arg_files(t_list *files);
void			print_arg_dir(t_list *files);
void			print_files(t_list *files);
void			full_file(t_l *file);
void			ft_print_one(t_l *file);
void			printblock(t_list *files);

char			*parse_name(char *name);
char			*first_parse_name(char *name);
int				ft_nbrlen(unsigned long long n);
void			r_param(t_l *file);
void			sub_folder_search_r(t_list *files);

// t_list			*ft_errnonot_found(t_list *files);
// void			ft_wrong_option(void);
// void			ft_other_err(t_l *file);
// t_l				*nff1(t_l *file, char *acl, char extacl, int symlink);
// t_l				*nff2(t_l *file, char *owner, char *group, long size);
// t_l				*nff3(t_l *file, time_t date, char *name, int status);
// t_l				*nff4(t_l *file, int blocks, int path);
// void			new_file(t_l *one, t_l *two, t_l *three);
// void			new_file_err(t_l *file, char *name);
// t_l				*new_file_err_2(t_l *file, char *name);

// char			*ft_lasttime(time_t filetime);
// char			*ft_owner(uid_t st_uid);
// char			*ft_group(gid_t st_gid);
// char			*ft_perm(mode_t st_mode);
// char			ft_extattr(char *name);

// void			del_list(void *content, size_t inutile);
// char			*parse_name(char *name);
// void			ft_put2endl(char *one, char *two);
// bool			check_arg(char *arglist, char c);

// t_list			*ft_t_l_sort_time(t_list *lst);
// t_list			*ft_t_l_sort_time_r(t_list *lst);
// t_list			*ft_t_l_sort_r(t_list *lst);
// t_list			*ft_t_l_sort(t_list *lst);
// t_list			*ft_sort_type(t_list *lst);
// t_list			*ft_fill(t_list *files, char *arglist, int mode, int count);

// void			printfiles(t_list *files, char *arglist);
// void			ft_print(t_list *files, t_list *head, char *arglist);
// void			full_file(t_l *file);
// void			ft_print_one(t_l *file, char *arglist);
#endif
