/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:48:47 by fparis            #+#    #+#             */
/*   Updated: 2023/12/20 21:41:58 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <assert.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"

char	*ft_join(char *str1, char *str2, int slash);
char	**ft_split(char *s, char charset);
void	*free_tab(char **tab, int n);
void	put_str(char *str, int fd);
int		check_limiter(char *str, char *limiter, char allow);
void	ft_error(char *func_err, char ***to_free, int to_close, int to_close2);
int		ft_strlen(char *str);
void	*free_args(char ***args, int skip);
char	***check_args(int argc, char **argv, char **envp);
void	cmd_not_found(char *cmd);

#endif
