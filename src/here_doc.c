/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:18:20 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/12 03:26:20 by babonnet         ###   ########.fr       */
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

static int	read_here_doc(char *path_name, int fd, char *end)
{
	char	*tmp;

	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		tmp = get_next_line(0);
		close(fd);
		fd = open(path_name, O_WRONLY | O_APPEND);
		if (fd == -1)
		{
			free(end);
			free(tmp);
			free(path_name);
			return (1);
		}
		if (!tmp || !ft_strcmp(tmp, end))
			break ;
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	close(fd);
	free(tmp);
	return (0);
}

static int	here_doc(char *end, char *program_name)
{
	int		fd;
	char	*path_name;

	path_name = create_tmp_file(&fd);
	if (fd == -1)
	{
		free(path_name);
		return (1);
	}
	if (read_here_doc(path_name, fd, end))
	{
		error_msg_here_doc(program_name);
		return (1);
	}
	dup_file_stdin(fd, path_name);
	unlink(path_name);
	free(path_name);
	return (0);
}

int	manage_here_doc(int ac, char **av, t_data *data)
{
	char	*cmp;

	if (ac < 6)
	{
		ft_putstr_fd("Error [too few arguments]", 2);
		return (0);
	}
	cmp = ft_strjoin(av[2], "\n");
	if (!cmp)
		return (0);
	if (here_doc(cmp, av[0]))
		return (1);
	free(cmp);
	data->size = ac - 4;
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (0);
}
