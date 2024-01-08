/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:09:08 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/04 19:18:23 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_cmd
{
	char	*cmd;
	char	**parameter;
	int		infile;
	int		outfile;
}			t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
	char	**env;
	int		size;
	int		outfile;
}			t_data;

void		*free_cmd(t_cmd *cmd, int size);
void		free_str_tab(char **tab);

t_cmd		*parsing_cmd(char **av, int ac, char **env);
int			manage_file(int ac, char **av, t_data *data);
char		*find_program_name(char *program);

#endif
