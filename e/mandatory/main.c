/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:10:02 by fparis            #+#    #+#             */
/*   Updated: 2023/12/20 19:18:36 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	rewrite_output(char *outfile, int *fd_pipe, char ***to_free)
{
	char	*line;
	int		fd_outfile;

	fd_outfile = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_outfile == -1)
		ft_error("open", to_free, fd_pipe[0], -1);
	line = get_next_line(fd_pipe[0], 0);
	while (line)
	{
		put_str(line, fd_outfile);
		free(line);
		line = get_next_line(fd_pipe[0], 0);
	}
	close(fd_outfile);
	close(fd_pipe[0]);
}

static void	exec_cmd(char **cmd, char *infile, char *outfile, char ***to_free)
{
	int	fd_file;
	int	fd_pipe[2];
	int	child_pid;

	if (pipe(fd_pipe) == -1)
		ft_error("pipe", NULL, -1, -1);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd_pipe[0]);
		fd_file = open(infile, O_RDWR);
		if (fd_file == -1)
			ft_error("open", to_free, fd_pipe[1], fd_file);
		if (dup2(fd_file, 0) == -1)
			ft_error("dup2", to_free, fd_pipe[1], -1);
		close(fd_file);
		if (dup2(fd_pipe[1], 1) == -1)
			ft_error("dup2", to_free, fd_pipe[1], -1);
		close(fd_pipe[1]);
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_error("execve", to_free, -1, -1);
	}
	waitpid(child_pid, NULL, 0);
	close(fd_pipe[1]);
	rewrite_output(outfile, fd_pipe, to_free);
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd_args;
	int		i;

	if (argc != 5 || !envp)
		exit(1);
	cmd_args = check_args(argc, argv, envp);
	if (cmd_args[0] == NULL)
		cmd_args = free_args(cmd_args, 1);
	if (access(argv[1], F_OK | R_OK) == -1)
		ft_error(argv[1], cmd_args, -1, -1);
	if (!cmd_args)
		exit(1);
	exec_cmd(cmd_args[0], argv[1], argv[argc - 1], cmd_args);
	i = 0;
	while (cmd_args[++i])
		exec_cmd(cmd_args[i], argv[argc - 1], argv[argc - 1], cmd_args);
	free_args(cmd_args, 0);
	return (0);
}
