/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:48:38 by babonnet          #+#    #+#             */
/*   Updated: 2023/12/29 21:42:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

t_cmd *parsing_cmd(char **av, int ac, int fd[2][2])
{
	t_cmd *cmd;
	int		i;

	cmd = ft_calloc(ac - 2, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < ac -3)
	{
		cmd[i].parameter = ft_split(av[i + 2], ' ');
		// error free all
		cmd[i].cmd = ft_strjoin("/usr/bin/", cmd[i].parameter[0]);
		// error free all
		i++;
	}
	//verif if all function exist
	(void)fd;
	return (cmd);

}

void print_cmd(t_cmd *cmd, int size)
{
	int i = 0;
	int j;

	while (i < size)
	{
		printf("%s\n", cmd[i].cmd);
		j = 0;
		while (cmd[i].parameter[j] != NULL)
		{
			printf("--\"%s\"\n", cmd[i].parameter[j]);
			j++;
		}
		i++;
	}
}

void free_cmd(t_cmd *cmd, int size)
{
	int i = 0;
	int j;

	while (i < size)
	{
		free(cmd[i].cmd);
		j = 0;
		while (cmd[i].parameter[j] != NULL)
		{
			free(cmd[i].parameter[j]);
			j++;
		}
		free(cmd[i].parameter);
		i++;
	}
	free(cmd);
}

void manage_pipe(int fd[2][2], int i)
{
	if (i == 0)
		dup2(fd[0][1], STDOUT_FILENO);
	if (i % 2 == 0)
	{

	}
	else
	{
		//
	}
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
		
}

int pipex(t_cmd *cmd, int *pid, int fd[2][2], int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		manage_pipe(fd, i);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			execve(cmd[i].cmd, cmd[i], NULL);
		}
		i++;
	}

}

int	main(int ac, char **av)
{
	t_cmd	*cmd;
	int		fd[2][2];
	int		*pid;

	pid = ft_calloc(ac - 3, sizeof(int));
	if (!pid)
		return (1);
	cmd = parsing_cmd(av, ac, fd);
	print_cmd(cmd , ac - 3);
	pipex(cmd, pid, fd, ac - 3);
	free_cmd(cmd, ac - 3);
	free(pid);
}
