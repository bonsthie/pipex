/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:59:17 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/04 19:21:04 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

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

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
