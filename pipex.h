/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:18:06 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/11 13:18:07 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include<stdio.h>
# include<fcntl.h>
# include<unistd.h>
# include<stdlib.h>
# include<sys/wait.h>
# include"ft_printf/ft_printf.h"

typedef struct s_pp
{
	int		end[2];
	int		fd_in;
	int		fd_out;
	char	**cmd_a;
	char	**cmd_b;
	char	*cmd_path;
	pid_t	pid_a;
	pid_t	pid_b;
}			t_pp;

char	**ft_alloc_fail(char **arr);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_exit(char *s);
char	*find_path(char **env);
size_t	ft_strlen(const char *s);
void	freeing(char **a, char **b, char **c, char *d);
void	ft_open(char **av, t_pp pp, char **path_s, char **env);
int		ft_child_a(t_pp pp, char **path_s, char **env);
int		ft_child_b(t_pp pp, char **path_s, char **env);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_close_ends(int a, int b, int c, int d);
int		ft_search(char *s, char c);
void	cmd_path(t_pp *pp, char *cmd, char **path_s);
void	ft_print_mess(t_pp pp, char **path_s, int flg);

#endif
