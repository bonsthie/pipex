/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:37:15 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/09 21:13:32 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

static void	here_doc(char *end)
{
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		return ;
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		tmp = get_next_line(0);
		if (!ft_strcmp(tmp, end))
			break ;
		ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
	free(tmp);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

static void	manage_here_doc(int ac, char **av, t_data *data)
{
	char	*cmp;

	if (ac < 6)
	{
		ft_putstr_fd("Error [too few arguments]", 2);
		return ;
	}
	cmp = ft_strjoin(av[2], "\n");
	if (!cmp)
		return ;
	here_doc(cmp);
	free(cmp);
	data->size = ac - 4;
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

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
