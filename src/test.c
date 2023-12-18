/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:12:29 by babonnet          #+#    #+#             */
/*   Updated: 2023/12/18 17:21:53 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"

int exec_bash(char *cmd, char **arg)
{
    if (execve(cmd, arg, NULL) == -1) 
    {
			perror("execve");
			return (1);
	}
	return (0);

}

int create_fork(int ac, int count, char *av, int *fd)
{
	char **arg;
    char *cmd;
	int	 pid;

	arg = ft_split(av, ' ');
	cmd = ft_strjoin("/usr/bin/", arg[0]);
	pid = fork();
	if (pid == 0)
	{
		if (count < 2)
		{
			write(1, "1\n", 2);
			if (ac < 2)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (exec_bash(cmd, arg) == 1)
				return (1);
		}
		else
		{
			write(1, "2\n", 2);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (exec_bash(cmd, arg) == 1)
				return (1);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		//while(arg)
		//{
		//	free(*arg);
		//	arg++;
		//}
		//free(arg);
		//free(cmd);
	}
	//
	return (0);
}

int main(int ac, char **av) 
{
	int fd[2];

	if (pipe(fd) == -1)
		return (1);
	ac--;
	int i = 1;

	while(i <= ac)
	{
		if (create_fork(ac, i, av[i], fd) == 1)
			return (1);
		i++;
	}
	return 0;
}

