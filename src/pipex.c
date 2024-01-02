/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:48:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/02 15:24:01 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
# include <fcntl.h>
# include <stdio.h>
#include <sys/wait.h>

void close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void manage_pipe(int fd[2][2], int i, int size, int outfile)
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
	close_pipe(fd[1]);
}

void wait_multiple_pid(int *pid, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void pipex(t_data data, int *pid, int fd[2][2])
{
	int i;

	i = 0;
	while (i < data.size)
	{
		if (pipe(fd[i % 2]) == -1)
		{
			perror("Error [pipe fail]\n");
			return ;
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			manage_pipe(fd, i, data.size, data.outfile);
			execve(data.cmd[i].cmd, data.cmd[i].parameter, data.env);
			perror("Error [execve fail]\n");
			return ;
		}
		if (i != 0)
			close_pipe(fd[(i + 1) % 2]);
		i++;
	}
	close_pipe(fd[i % 2]);
	wait_multiple_pid(pid, data.size);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd[2][2];
	int		*pid;

	if (ac < 5)
	{
		perror("Error [too few arguments]");
		return 1;
	}
	data.size = manage_file(ac, av, &data);
	if (data.size == 0)
		return (1);
	pid = ft_calloc(data.size, sizeof(int));
	if (!pid)
		return (1);
	data.env = env;
	data.cmd = parsing_cmd(av, ac);
	if (data.cmd != NULL)
	{
		pipex(data, pid, fd);
		free_cmd(data.cmd, data.size);
	}
	free(pid);
	return (0);
}
