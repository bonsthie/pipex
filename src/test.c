/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonnet <bbonnet@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:12:29 by babonnet          #+#    #+#             */
/*   Updated: 2023/12/19 01:07:12 by bbonnet          ###   ########.fr       */
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



int create_fork(int ac, char **av, int *prev_fd) {
    int fd[2];
    char **arg;
    char *cmd;
    int pid;

    if (ac <= 1) {
        fprintf(stderr, "No commands provided.\n");
        return 1;
    }

    for (int i = 1; i < ac; i++) {
        if (i < ac - 1) { // Not the last command, so create a pipe
            if (pipe(fd) == -1) {
                perror("pipe");
                return 1;
            }
        }

        arg = ft_split(av[i], ' ');
        cmd = ft_strjoin("/usr/bin/", arg[0]);

        pid = fork();
        if (pid == 0) { // Child process
            if (i > 1) { // Not the first command
                dup2(prev_fd[0], STDIN_FILENO);
                close(prev_fd[0]);
                close(prev_fd[1]);
            }
            if (i < ac - 1) { // Not the last command
                close(fd[0]); // Close read end of the current pipe
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]); // Close write end after duplicating
            }
            execve(cmd, arg, NULL);
            perror("execve");
            exit(EXIT_FAILURE); // Exit if execve fails
        } else if (pid < 0) {
            perror("fork");
            return 1;
        }

        // In parent process
        if (i > 1) {
            close(prev_fd[0]); // Close previous read end
            close(prev_fd[1]); // Close previous write end
        }
        if (i < ac - 1) {
            prev_fd[0] = fd[0]; // Pass the read end of the current pipe to the next iteration
            prev_fd[1] = fd[1]; // Pass the write end of the current pipe to the next iteration
        }

        // Freeing memory is essential but you mentioned it's not needed for now

        waitpid(pid, NULL, 0); // Wait for the child to finish
    }
    return 0;
}


int main(int ac, char **av) 
{
    int fd[2];

    pipe(fd);
    if (create_fork(ac, av, fd) == 1)
        return (1);
    return (0);
}

