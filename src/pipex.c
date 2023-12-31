/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:48:38 by babonnet          #+#    #+#             */
/*   Updated: 2023/12/31 01:13:15 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdio.h>
# include <fcntl.h>
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

int outfile;

void manage_pipe(int fd[2][2], int i, int size)
{
	if (i == 0)
		dup2(fd[0][1], STDOUT_FILENO);
	else if (i == size - 1)
	{
		dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
		dup2(fd[i % 2][1], STDOUT_FILENO);
	}
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
}

void pipex(t_cmd *cmd, int *pid, int fd[2][2], int size, char **env)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		if (i == 0)
			pipe(fd[0]);
		else if (i < size - 1)
			pipe(fd[i % 2]);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			manage_pipe(fd, i, size);

			execve(cmd[i].cmd, cmd[i].parameter, env);
			write(2, "Error\n", 6);
		}
		if (i != 0)
		{
			close(fd[(i + 1) % 2][0]);
			close(fd[(i + 1) % 2][1]);
		}
		i++;
	}
	close(fd[i % 2][0]);
	close(fd[i % 2][1]);
	j = 0;
	while (j++ < size)
	{
		//printf("test\n");
		waitpid(pid[j], NULL, 0);
		j++;
	}

}


int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd;
	int		fd[2][2];
	int		*pid;
	int		infile;
	//int		outfile;

	infile = open(av[1], O_RDONLY);
	outfile = open(av[ac - 1], O_WRONLY);
	if (infile < 0 || outfile < 0)
		return (0);
	//char test[30];
	dup2(infile, STDIN_FILENO);
	//read(STDIN_FILENO, test, 30);
	//printf("%s\n", test);

	close(infile);
	pid = ft_calloc(ac - 3, sizeof(int));
	if (!pid)
		return (1);
	cmd = parsing_cmd(av, ac, fd);
	//print_cmd(cmd , ac - 3);
	pipex(cmd, pid, fd, ac - 3, env);
	free_cmd(cmd, ac - 3);
	free(pid);
}
