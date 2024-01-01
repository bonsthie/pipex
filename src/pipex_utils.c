/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:59:17 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/01 21:19:27 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

void	*free_cmd(t_cmd *cmd, int size)
{
	int	i;
	int	j;

	i = 0;
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
	return (NULL);
}

char	*find_cmd(char *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strdup(cmd);
	if (access(cmd_path, X_OK) != -1)
		return (cmd_path);
	free(cmd_path);
	cmd_path = ft_strjoin("/usr/bin/", cmd);
	if (access(cmd_path, X_OK) != -1)
		return (cmd_path);
	free(cmd_path);
	cmd_path = ft_strjoin("/bin/", cmd);
	if (access(cmd_path, X_OK) != -1)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

t_cmd	*parsing_cmd(char **av, int ac)
{
	t_cmd	*cmd;
	int		i;

	cmd = ft_calloc(ac - 2, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < ac - 3)
	{
		cmd[i].parameter = ft_split(av[i + 2], ' ');
		if (cmd[i].parameter == NULL)
			return (free_cmd(cmd, i));
		cmd[i].cmd = find_cmd(cmd[i].parameter[0]);
		if (cmd[i].cmd == NULL)
		{
			perror("Error [Command doesn't exist]");
			return (free_cmd(cmd, i));
		}
		i++;
	}
	return (cmd);
}
