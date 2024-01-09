/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:37:15 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/08 23:41:01 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

static void	error_msg(char *program_name, char *cmd)
{
	char	*name;

	name = find_program_name(program_name);
	write(2, name, ft_strlen(name));
	ft_putstr_fd(": no such file or directory: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

int	manage_file(int ac, char **av, t_data *data)
{
	int	infile;
	int	size;

	size = ac - 3;
	infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || data->outfile < 0)
	{
		error_msg(av[0], av[1]);
		return (0);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (size);
}
