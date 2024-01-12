/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:09:08 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/12 02:59:19 by babonnet         ###   ########.fr       */
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

int			manage_here_doc(int ac, char **av, t_data *data);

void		error_msg_cmd(char *program_name, char **cmd);
void		error_msg_file(char *program_name, char *cmd);
void		error_msg_here_doc(char *program_name);

t_cmd		*parsing_cmd(char **av, int ac, char **env, char *program_name);
int			parsing(t_data *data, int ac, char **av);

#endif
