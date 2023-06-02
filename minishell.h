/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarlida <bkarlida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:37:26 by burakkarlid       #+#    #+#             */
/*   Updated: 2023/06/02 19:39:17 by bkarlida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"

typedef struct z_list
{
	char			*content;
	char			flag;// pipe rdirect ve tırnak varsa gösterir yoksa 'b' yazar
	int				extra_flag;//kullanım dışı
	struct z_list	*next;
}					link_list;

struct s_var
{
	int		lparse_int_value;//beklemede
	link_list	*lst;
	char	quot_flag;// tırnak flagleri
	char	*cont; // parser kısmında kullanılan geçici değişken
	char	rdr_flag;//oluşturulan listelere flag ataması yapılır
	int		extra_rdr_flag;//beklemede
	//int		error_flag;//kullanım dışı
	int		lst_size; // parserdan sonra oluşan listenin uzunluğu
	char	**str; // bütün lst->contentlerinin toplandığı double array
	char	**b_str;// kullanım dışı
	char	**env; // mainden env çekildi
	int		env_size; // envsize
	char	*pwd_new; // değişen pwd nin yeni yolunu env eklemek için
	char	**export; // export
	int		export_size;
	char	*ex_int;
	
}	g_var;

void		start_parser(char *line);
int			find_helper(char **p, char *a);
int			arg_isdigit(char *a);
void    	ft_unset(char *str);
void		ft_exit(void);
void		ft_env(void);
void    	ft_pwd(void);
void		ft_pwd(void);
int			ft_echo_is_null(char *str);
void		ft_echo(int	k);
int			command_built(void);
int			strequal(char *str, char *ptr); // özel fonksiyon
void		quot_parser(char *line, int *i);
void		rdr_parser(char *line, int *i);
void		consecutive_rdr_parser(char *line, int *i);
void		link_lstadd_back(link_list **lst, link_list *new);
void		link_lstclear(link_list **lst);
void		link_lstdelone(link_list *lst);
link_list	*link_lstlast(link_list *lst);
link_list	*link_lstnew(char *content, char flag);
int			link_lstsize(link_list *lst);
int			cd_func(int i);
char 	   *cut_helper_test(const char *str);

#endif