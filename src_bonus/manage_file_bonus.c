/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:37:15 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/11 17:31:52 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <fcntl.h>
#include <unistd.h>

static void	manage_file(int ac, char **av, t_data *data)
{
	int	infile;

	data->size = ac - 3;
	infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || data->outfile < 0)
	{
		error_msg_file(av[0], av[1]);
		data->size = 0;
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
}

int	parsing(t_data *data, int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error [too few arguments]", 2);
		return (2);
	}
	if (!data->env)
	{
		ft_putstr_fd("Error [env is empty]", 2);
		return (2);
	}
	if (!ft_strcmp(av[1], "here_doc"))
	{
		manage_here_doc(ac, av, data);
		return (1);
	}
	manage_file(ac, av, data);
	if (data->size == 0)
		return (2);
	return (0);
}
