/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:37:15 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/02 14:51:42 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int manage_file(int ac, char **av, t_data *data)
{
	int infile;
	int size;

	size = ac - 3;
	infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (infile < 0 || data->outfile < 0)
	{
		perror("Error [file dosen't exist]");
		return (0);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (size);
}
