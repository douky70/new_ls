/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 08:42:21 by akeiflin          #+#    #+#             */
/*   Updated: 2019/03/02 17:34:57 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <stdbool.h>
# include <string.h>
# include "libft.h"

# define AVAILABLE_ARG "lRart"
# ifndef MAXNAMLEN
#  define MAXNAMLEN 255
# endif

typedef struct stat	t_stat;
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
	char		*size;
	time_t		date;
	int			block;
	int			error;
	int			type;
	int			padding[3];
	int			fullname;
	char		*device;
}				t_l;

void			ft_wrong_option(void);
void			print_err(t_l *file);

char			*ft_parse_arg(int argc, char **argv);
t_list			*ft_arg_file(int argc, char **argv);
int				check_arg(char c);

void			fill_one(t_l *file, struct stat buff);
void			fill(t_list *files);
void			fill_dir(t_l *directory);
void			fill_padding(t_list *files, int skipfolders);
void			nff(t_l *file, char *acl, char *extacl, int symlink);
void			nff2(t_l *file, char *owner, char *group, char *size);
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

char			*device(dev_t st_rdev);
int				is_dir(t_stat buff, t_l *file);
#endif
