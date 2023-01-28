/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:56:01 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/23 13:56:02 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pipex.h"

static	void	ft_a(t_pp pp, char **path_s, char **env)
{
	ft_close_ends(pp.end[0], pp.fd_out, -1, -1);
	if (ft_child_a(pp, path_s, env) == -1)
		ft_exit("execve failed in the first child process\n");
}

static	void	ft_b(t_pp pp, char **path_s, char **env)
{
	ft_close_ends(pp.end[1], pp.fd_in, -1, -1);
	if (ft_child_b(pp, path_s, env) == -1)
		ft_exit("execve failed in the second child process\n");
}

static	void	ft_evol(t_pp pp, char **path_s, char **env)
{
	pp.pid_a = fork();
	if (pp.pid_a == -1)
	{
		ft_print_mess(pp, path_s, 1);
	}
	if (pp.pid_a == 0)
	{
		if (pp.fd_in == -1)
		{
			freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
			ft_close_ends(pp.end[1], pp.end[0], pp.fd_out, -1);
			exit(1);
		}
		ft_a(pp, path_s, env);
	}
	pp.pid_b = fork();
	if (pp.pid_b == -1)
		ft_print_mess(pp, path_s, 0);
	if (pp.pid_b == 0)
		ft_b(pp, path_s, env);
	ft_close_ends(pp.fd_in, pp.fd_out, pp.end[1], pp.end[0]);
	waitpid(pp.pid_b, NULL, 0);
	waitpid(pp.pid_a, NULL, 0);
	freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
}

static	void	ft_norm1(t_pp pp, char **path_s, char **av, int flg)
{
	if (flg)
		freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
	ft_printf("term: %s: ", av[1]);
	perror("");
}

void	ft_open(char **av, t_pp pp, char **path_s, char **env)
{
	pp.fd_in = open(av[1], O_RDONLY);
	if (pp.fd_in < 0)
		ft_norm1(pp, path_s, av, 0);
	pp.fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pp.fd_out < 0)
	{
		ft_norm1(pp, path_s, av, 1);
		close(pp.fd_in);
		return ;
	}
	if (pipe(pp.end) == -1)
	{
		freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
		ft_close_ends(pp.fd_in, pp.fd_out, -1, -1);
		ft_exit("failed to create the pipe");
	}
	ft_evol(pp, path_s, env);
}
