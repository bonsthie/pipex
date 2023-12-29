/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:10:02 by fparis            #+#    #+#             */
/*   Updated: 2023/12/29 23:05:35 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	file_transfer(char *infile, char *outfile)
{
	int		fd_infile;
	int		fd_outfile;
	char	*line;

	fd_infile = open(infile, O_RDWR);
	if (fd_infile == -1)
		ft_error("open", NULL, -1, -1);
	fd_outfile = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd_outfile == -1)
		ft_error("open", NULL, fd_infile, -1);
	line = get_next_line(fd_infile, 0);
	while (line)
	{
		put_str(line, fd_outfile);
		free(line);
		line = get_next_line(fd_infile, 0);
	}
	close(fd_infile);
	close(fd_outfile);
	if (unlink(infile) == -1)
		ft_error("unlink", NULL, -1, -1);
}

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

static int	here_doc_launcher(char *outfile, char *sep, char ***cmd_args)
{
	int		i;
	char	*temp_output;

	temp_output = here_doc(sep, outfile, cmd_args);
	i = 0;
	while (cmd_args[i])
	{
		exec_cmd(cmd_args[i], temp_output, temp_output, cmd_args);
		i++;
	}
	free_args(cmd_args, 0);
	file_transfer(temp_output, outfile);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd_args;
	int		i;

	if ((argc < 5 || !envp) || (check_limiter(argv[1], "here_doc", '\0')
			&& argc < 6))
		exit(1);
	cmd_args = check_args(argc, argv, envp);
	if (cmd_args[0] == NULL)
		cmd_args = free_args(cmd_args, 1);
	if (check_limiter(argv[1], "here_doc", '\0') == 0
		&& access(argv[1], F_OK | R_OK) == -1)
		ft_error(argv[1], cmd_args, -1, -1);
	if (!cmd_args)
		exit(1);
	if (check_limiter(argv[1], "here_doc", '\0'))
		return (here_doc_launcher(argv[argc - 1], argv[2], cmd_args));
	exec_cmd(cmd_args[0], argv[1], argv[argc - 1], cmd_args);
	i = 0;
	while (cmd_args[++i])
		exec_cmd(cmd_args[i], argv[argc - 1], argv[argc - 1], cmd_args);
	free_args(cmd_args, 0);
	return (0);
}
