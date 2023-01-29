/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:51:33 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/24 17:51:34 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pipex.h"

static	void	ft_access(t_pp *pp, char *join, char *c, char **tmp)
{
	if (access(join, X_OK) != 0)
	{
		ft_close_ends(pp->fd_in, pp->fd_out, pp->end[0], pp->end[1]);
		free(c);
		freeing(pp->cmd_a, pp->cmd_b, tmp, join);
		ft_printf("term: permission denied\n");
		exit(1);
	}
	return ;
}

static	void	ft_free(t_pp *pp, char **tmp, char *cmd)
{
	if (ft_search(cmd, '/'))
		ft_printf("term: no such file or directory: %s\n", cmd);
	else
		ft_printf("term: command not found: %s\n", cmd);
	freeing(pp->cmd_a, pp->cmd_b, tmp, NULL);
	exit(1);
}

static	void	ft_find(t_pp *pp, char **join, char **path_s, char *cmd)
{
	char	*c;

	while (*path_s)
	{
		c = ft_strjoin(*path_s, "/");
		*join = ft_strjoin(c, cmd);
		if (access(*join, F_OK) == 0)
		{
			ft_access(pp, *join, c, path_s);
			pp->cmd_path = *join;
			break ;
		}
		free(*join);
		free(c);
		*join = NULL;
		path_s++;
	}
}

void	cmd_path(t_pp *pp, char *cmd, char **path_s)
{
	char	*join;

	join = NULL;
	//if the cmd has a '/' means that we already have the program path.
	//so, we directly check if this program exists and if we have the permissions to execute it.
	if (ft_search(cmd, '/'))
	{
		//F_OK flag tells if the file exists.
		if (access(cmd, F_OK) == 0)
		{
			ft_access(pp, cmd, NULL, path_s);
			pp->cmd_path = cmd;
			return ;
		}
		join = NULL;
	}
	else
	{
		//else we look for the command path
		ft_find(pp, &join, path_s, cmd);
	}
	if (join == NULL)
	{
		//if the loop terminates and the value of join is NULL that means that the program/command does not exist 
		ft_free(pp, path_s, cmd);
	}
}
