/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:01:07 by fparis            #+#    #+#             */
/*   Updated: 2023/12/20 00:23:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	***make_args_tab(int argc, char **argv)
{
	int		i;
	int		nb_args;
	char	***args;

	if (check_limiter(argv[1], "here_doc", '\0'))
		nb_args = argc - 4;
	else
		nb_args = argc - 3;
	args = malloc((nb_args + 1) * sizeof(char **));
	if (!args)
		exit(1);
	args[nb_args] = NULL;
	i = 0;
	while (i < nb_args)
	{
		args[i] = ft_split(argv[i + (argc - nb_args - 1)], ' ');
		if (args[i] == NULL)
		{
			free_args(args);
			return (NULL);
		}
		i++;
	}
	return (args);
}

static int	is_path(char *str)
{
	char	*check;
	int		i;
	int		res;

	check = malloc(6 * sizeof(char));
	if (!check)
		exit(1);
	i = 0;
	while (i < 5)
	{
		check[i] = str[i];
		i++;
	}
	check[i] = '\0';
	res = check_limiter(check, "PATH=", '\0');
	free(check);
	return (res);
}

static char	**get_paths(char **envp)
{
	int		i;
	char	**paths;
	char	*first_arg;

	i = 0;
	while (envp[i] && is_path(envp[i]) != 1)
		i++;
	paths = ft_split(envp[i], ':');
	if (!paths)
		exit(1);
	first_arg = malloc((ft_strlen(paths[0]) - 4) * sizeof(char));
	if (!first_arg)
	{
		free_tab(paths, 0);
		exit(1);
	}
	i = 0;
	while (paths[0][i + 4])
	{
		first_arg[i] = paths[0][i + 5];
		i++;
	}
	free(paths[0]);
	paths[0] = first_arg;
	return (paths);
}

static int	put_path(char **arg, char **paths, char ***to_free)
{
	char	*test;
	int		i;

	i = 0;
	while (paths[i])
	{
		test = ft_join(paths[i], arg[0], 1);
		if (!test)
		{
			free_tab(paths, 0);
			free_args(to_free);
			exit(1);
		}
		if (access(test, F_OK | X_OK) == 0)
		{
			free(arg[0]);
			arg[0] = test;
			return (1);
		}
		free(test);
		i++;
	}
	return (0);
}

char	***check_args(int argc, char **argv, char **envp)
{
	int		i;
	char	***args;
	char	**paths;

	paths = get_paths(envp);
	args = make_args_tab(argc, argv);
	if (!args)
	{
		free_tab(paths, 0);
		exit(1);
	}
	i = 0;
	while (args[i])
	{
		if (!put_path(args[i], paths, args)
			&& access(args[i][0], F_OK | X_OK) == -1)
		{
			free_tab(paths, 0);
			ft_error(args[i][0], args, -1, -1);
		}
		i++;
	}
	free_tab(paths, 0);
	return (args);
}
