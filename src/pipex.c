/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:48:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/09 21:15:31 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static void	close_pipe(int fd[2])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

static void	manage_pipe(int fd[2][2], int i, int size, int outfile)
{
	if (i == 0)
		dup2(fd[0][1], STDOUT_FILENO);
	else if (i == size - 1)
	{
		dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else
	{
		dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
		dup2(fd[i % 2][1], STDOUT_FILENO);
	}
	close_pipe(fd[0]);
	if (i > 0)
		close_pipe(fd[1]);
}

static void	wait_multiple_pid(int *pid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

static void	pipex(t_data data, int *pid, int fd[2][2])
{
	int	i;

	i = -1;
	while (++i < data.size)
	{
		if (pipe(fd[i % 2]) == -1)
		{
			ft_putstr_fd("Error [pipe fail]\n", 2);
			return ;
		}
		if (data.cmd[i].cmd)
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				manage_pipe(fd, i, data.size, data.outfile);
				execve(data.cmd[i].cmd, data.cmd[i].parameter, data.env);
				return ;
			}
		}
		if (i != 0)
			close_pipe(fd[(i + 1) % 2]);
	}
	close_pipe(fd[i % 2]);
	wait_multiple_pid(pid, data.size);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		here_doc;
	int		fd[2][2];
	int		*pid;

	data.env = env;
	here_doc = parsing(&data, ac, av);
	if (here_doc == 2)
		return (1);
	pid = ft_calloc(data.size, sizeof(int));
	if (!pid)
		return (1);
	data.cmd = parsing_cmd(&av[here_doc], ac - here_doc, env);
	if (data.cmd != NULL)
	{
		pipex(data, pid, fd);
		free_cmd(data.cmd, data.size);
	}
	free(pid);
	return (0);
}
