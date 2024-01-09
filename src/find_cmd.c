/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:13:09 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/09 01:08:40 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>

char	*find_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	if (access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, X_OK) != -1)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*find_program_name(char *program)
{
	char	*name;

	name = ft_strrchr(program, '/');
	if (!name)
		return (program);
	return (name + 1);
}

static void	error_msg(char *program_name, char *cmd)
{
	char	*name;

	name = find_program_name(program_name);
	write(2, name, ft_strlen(name));
	ft_putstr_fd(": command not found", 2);
	write(2, ": ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

char	**create_path(char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) && env[i] != NULL)
		i++;
	if (env[i] == NULL)
		return (NULL);
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		if (path[i][0] && path[i][ft_strlen(path[i]) - 1] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			if (tmp)
			{
				free(path[i]);
				path[i] = tmp;
			}
		}
		i++;
	}
	return (path);
}

t_cmd	*parsing_cmd(char **av, int ac, char **env)
{
	t_cmd	*cmd;
	int		i;
	char	**path;

	path = create_path(env);
	cmd = ft_calloc(ac - 2, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < ac - 3)
	{
		cmd[i].parameter = ft_split(av[i + 2], ' ');
		if (cmd[i].parameter)
			cmd[i].cmd = find_cmd(cmd[i].parameter[0], path);
		else
			cmd[i].cmd = NULL;
		if (cmd[i].cmd == NULL && cmd[i].parameter)
			error_msg(av[0], cmd[i].parameter[0]);
		i++;
	}
	if (path)
		free_str_tab(path);
	return (cmd);
}
