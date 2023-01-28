/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:34:46 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/20 09:34:48 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pipex.h"

void	ft_exit(char *s)
{
	ft_printf("%s", s);
	exit(1);
}

char	*find_path(char **env)
{
	if (env == NULL || env[0] == NULL)
		return (NULL);
	while (*env)
	{
		if (ft_strncmp("PATH", *env, 4) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

void	ft_close_ends(int a, int b, int c, int d)
{
	close(a);
	close(b);
	close(c);
	close(d);
}

void	freeing(char **a, char **b, char **c, char *d)
{
	ft_alloc_fail(a);
	ft_alloc_fail(b);
	ft_alloc_fail(c);
	free(d);
}

void	ft_print_mess(t_pp pp, char **path_s, int flg)
{
	freeing(pp.cmd_a, pp.cmd_b, path_s, NULL);
	ft_close_ends(pp.fd_in, pp.fd_out, pp.end[1], pp.end[0]);
	if (flg)
		ft_exit("failed to create the first child process");
	else
		ft_exit("failed to create the second child process");
	return ;
}
