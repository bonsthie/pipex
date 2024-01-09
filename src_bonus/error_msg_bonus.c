/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:02:09 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/09 21:13:43 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

static char	*find_program_name(char *program)
{
	char	*name;

	name = ft_strrchr(program, '/');
	if (!name)
		return (program);
	return (name + 1);
}

void	error_msg_cmd(char *program_name, char **cmd)
{
	char	*name;

	name = find_program_name(program_name);
	write(2, name, ft_strlen(name));
	ft_putstr_fd(": command not found: ", 2);
	if (cmd)
		write(2, cmd[0], ft_strlen(cmd[0]));
	else
		ft_putstr_fd("\" \"", 2);
	write(2, "\n", 1);
}

void	error_msg_file(char *program_name, char *cmd)
{
	char	*name;

	name = find_program_name(program_name);
	write(2, name, ft_strlen(name));
	ft_putstr_fd(": no such file or directory: ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}
