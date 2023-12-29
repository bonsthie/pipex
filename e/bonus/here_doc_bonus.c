/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:12:29 by fparis            #+#    #+#             */
/*   Updated: 2023/12/20 20:06:05 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*here_doc(char *limiter, char *outfile_name, char ***to_free)
{
	char	*str;
	int		fd_file;
	char	*outfile_temp;

	if (check_limiter(outfile_name, "temp", '\0'))
		outfile_temp = "temp2";
	else
		outfile_temp = "temp";
	fd_file = open(outfile_temp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_file == -1)
		ft_error("open", to_free, -1, -1);
	str = get_next_line(0, 0);
	if (!str)
		ft_error("get_next_line", to_free, fd_file, -1);
	while (!check_limiter(str, limiter, '\n'))
	{
		put_str(str, fd_file);
		free(str);
		str = get_next_line(0, 0);
		if (!str)
			ft_error("get_next_line", to_free, fd_file, -1);
	}
	free(str);
	close(fd_file);
	return (outfile_temp);
}
