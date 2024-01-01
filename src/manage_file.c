/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:37:15 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/01 21:17:17 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int manage_file(int ac, char **av, t_data *data)
{
	int infile;
	int size;

	size = ac - 3;
	infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY);
	if (infile < 0 || data->outfile < 0)
		return (0);
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (size);
}
