/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:18:20 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/10 15:25:18 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>

static char	*create_tmp_file(int *fd)
{
	char	*file;
	int		fd_random;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (NULL);
	file = ft_calloc(20, sizeof(char));
	if (!file)
	{
		close(fd_random);
		return (NULL);
	}
	while (1)
	{
		if (read(fd_random, file, 20) == -1)
			return (NULL);
		file[0] = '.';
		file[19] = '\0';
		*fd = open(file, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (*fd != -1)
		{
			close(fd_random);
			return (file);
		}
	}
}

static void	dup_file_stdin(int fd, char *path_name)
{
	fd = open(path_name, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	here_doc(char *end)
{
	int		fd;
	char	*path_name;
	char	*tmp;

	path_name = create_tmp_file(&fd);
	if (fd == -1)
	{
		free(path_name);
		return ;
	}
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		tmp = get_next_line(0);
		if (!ft_strcmp(tmp, end))
			break ;
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	close(fd);
	free(tmp);
	dup_file_stdin(fd, path_name);
	unlink(path_name);
	free(path_name);
}

void	manage_here_doc(int ac, char **av, t_data *data)
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
