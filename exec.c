/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:15:51 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/20 10:15:52 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pipex.h"

int	ft_child_a(t_pp pp, char **path_s, char **env)
{
	//commands read from standard input and display their output to the standard output
	//So that, I should duplicate the stdin by the fd of the input file and the stdout by the write end of the pipe
	if (dup2(pp.end[1], 1) == -1 || dup2(pp.fd_in, 0) == -1)
		ft_exit("failed to duplicate the file descriptor");
	//closing the input file and the write end of the pipe after dup2 function.
	ft_close_ends(pp.end[1], pp.fd_in, -1, -1);
	//finding command path
	cmd_path(&pp, pp.cmd_a[0], path_s);
	//freeing
	freeing(pp.cmd_b, path_s, NULL, NULL);
	//executing the cmd via execve function, if the execve succeeds it will return nothing and terminate the process, else it will return -1.
	execve(pp.cmd_path, pp.cmd_a, env);
	freeing(pp.cmd_a, NULL, NULL, pp.cmd_path);
	return (-1);
}
//the same process as the child_a function
int	ft_child_b(t_pp pp, char **path_s, char **env)
{
	if (dup2(pp.end[0], 0) == -1 || dup2(pp.fd_out, 1) == -1)
		ft_exit("failed to duplicate the file descriptor");
	ft_close_ends(pp.end[0], pp.fd_out, -1, -1);
	cmd_path(&pp, pp.cmd_b[0], path_s);
	freeing(pp.cmd_a, path_s, NULL, NULL);
	execve(pp.cmd_path, pp.cmd_b, env);
	freeing(pp.cmd_b, NULL, NULL, pp.cmd_path);
	return (-1);
}
