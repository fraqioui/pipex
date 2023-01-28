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
	//close unused fds
	ft_close_ends(pp.end[0], pp.fd_out, -1, -1);
	if (ft_child_a(pp, path_s, env) == -1)
		ft_exit("execve failed in the first child process\n");
}

static	void	ft_b(t_pp pp, char **path_s, char **env)
{
	//close unused fds
	ft_close_ends(pp.end[1], pp.fd_in, -1, -1);
	if (ft_child_b(pp, path_s, env) == -1)
		ft_exit("execve failed in the second child process\n");
}

static	void	ft_evol(t_pp pp, char **path_s, char **env)
{
	//create the first child process via fork system call.
	pp.pid_a = fork();
	if (pp.pid_a == -1)
	{
		ft_print_mess(pp, path_s, 1);
	}
	//if fork returns 0 that means that we are on the child process
	if (pp.pid_a == 0)
	{
		//freeing and closing if open function failed to open the input file
		if (pp.fd_in == -1)
		{
			freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
			ft_close_ends(pp.end[1], pp.end[0], pp.fd_out, -1);
			exit(1);
		}
		//else executing the first command of the pipe
		ft_a(pp, path_s, env);
	}
	//create the second child process to execute the second command of the pipe
	//just the parent process will fork here because the child process will terminate due to execve function execution, but if it fails the program exits.
	pp.pid_b = fork();
	if (pp.pid_b == -1)
		ft_print_mess(pp, path_s, 0);
	//pp.pid_b is equal to 0 means that I am in child process
	if (pp.pid_b == 0)
		ft_b(pp, path_s, env);
	//close all open files in the parent process since they are not useful anymore
	ft_close_ends(pp.fd_in, pp.fd_out, pp.end[1], pp.end[0]);
	//waitpid is responsible for helping the parent process to wait for its childs to terminate their execution
	waitpid(pp.pid_b, NULL, 0);
	waitpid(pp.pid_a, NULL, 0);
	//deallocate memory
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
	//open the input file for read only
	pp.fd_in = open(av[1], O_RDONLY);
	//even if the open function failed, I should create the output file.
	//perror will specify the reason why it couldn't the file. (like: permission denied || no such file or directory).
	if (pp.fd_in < 0)
		ft_norm1(pp, path_s, av, 0);
	//create the output file for write & truncate.
	pp.fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	//if the open file to create the file I should dallocate memory and close the input file.
	if (pp.fd_out < 0)
	{
		ft_norm1(pp, path_s, av, 1);
		close(pp.fd_in);
		return ;
	}
	//create the pipe via pipe function.
	if (pipe(pp.end) == -1)
	{
		freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
		ft_close_ends(pp.fd_in, pp.fd_out, -1, -1);
		ft_exit("failed to create the pipe");
	}
	ft_evol(pp, path_s, env);
}
