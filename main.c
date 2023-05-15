/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:17:59 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/11 13:18:01 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pipex.h"

static	void	ft_setting(char **av, char **env)
{
	t_pp	pp;
	char	*path;
	char	**path_s;

	//split the commands
	pp.cmd_a = ft_split(av[2], ' ');
	pp.cmd_b = ft_split(av[3], ' ');
	//finding the PATH
	path = find_path(env);
	path_s = NULL;
	//if the path does not exist, the program displays the "command not found" message but keeps working to create the output file as shell.
	if (path == NULL)
	{
		ft_printf("term: command not found: %s\n", pp.cmd_a[0]);
		ft_printf("term: command not found: %s\n", pp.cmd_b[0]);
	}
	else
	{
		//splitting the path
		path_s = ft_split(path, ':');
		if (path_s == NULL)
		{
			freeing(pp.cmd_a, pp.cmd_b, NULL, NULL);
			ft_exit("failed to separate the env path\n");
		}
	}
	ft_open(av, pp, path_s, env);
}

int	main(int ac, char **av, char **env)
{
	//The number of arguments should be 5
	if (ac == 5)
		ft_setting(av, env);
	else
		ft_exit("invalid number of arguments\n");
	return (0);
}
