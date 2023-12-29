/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:12:29 by fparis            #+#    #+#             */
/*   Updated: 2023/12/20 00:08:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_limiter(char *str, char *limiter, char allow)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != allow)
	{
		if (str[i] != limiter[i])
			return (0);
		i++;
	}
	if (str[i] == allow && limiter[i] == '\0')
		return (1);
	return (0);
}

void	put_str(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}
