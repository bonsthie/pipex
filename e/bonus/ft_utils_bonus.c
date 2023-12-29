/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:50:39 by fparis            #+#    #+#             */
/*   Updated: 2023/12/20 20:06:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

char	*ft_join(char *str1, char *str2, int slash)
{
	char	*res;
	int		i;
	int		i2;
	int		total_len;

	total_len = ft_strlen(str1) + ft_strlen(str2) + slash;
	res = malloc((total_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[total_len] = '\0';
	i = 0;
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	if (slash)
		res[i] = '/';
	i2 = 0;
	while (str2[i2])
	{
		res[i + i2 + slash] = str2[i2];
		i2++;
	}
	return (res);
}

void	ft_error(char *func_err, char ***to_free, int to_close, int to_close2)
{
	perror(func_err);
	if (to_free)
		free_args(to_free, 0);
	if (to_close >= 0)
		close(to_close);
	if (to_close2 >= 0)
		close(to_close2);
	exit(1);
}

void	*free_args(char ***args, int skip)
{
	int	i;

	i = skip;
	if (!args)
		return (NULL);
	while (args[i])
	{
		free_tab(args[i], 0);
		i++;
	}
	free(args);
	return (NULL);
}

void	cmd_not_found(char *cmd)
{
	put_str("zsh: command not found: ", 1);
	put_str(cmd, 1);
	put_str("\n", 1);
}
