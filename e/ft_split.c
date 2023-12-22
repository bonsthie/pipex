/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:10:00 by fparis            #+#    #+#             */
/*   Updated: 2023/12/19 19:02:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**gen_tab(char *str, char charsep)
{
	int		i;
	int		nb_args;
	char	**res;

	i = 0;
	nb_args = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == charsep)
			i++;
		if (str[i] && str[i] != charsep)
			nb_args++;
		while (str[i] && str[i] != charsep)
			i++;
	}
	if (nb_args == 0)
		return (NULL);
	res = malloc((nb_args + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[nb_args] = NULL;
	return (res);
}

static char	*make_tab(char const *s, int start, int end)
{
	char	*tab;
	int		i;

	tab = malloc(((end - start) + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = start;
	while (i < end)
	{
		tab[i - start] = s[i];
		i++;
	}
	tab[i - start] = '\0';
	return (tab);
}

void	*free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n || (n == 0 && tab[i] != NULL))
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	return (NULL);
}

char	**ft_split(char *s, char charsep)
{
	char	**res;
	int		i;
	int		nb_word;
	int		word_start;

	res = gen_tab(s, charsep);
	nb_word = -1;
	i = 0;
	while (res != NULL && s[i])
	{
		while (s[i] && s[i] == charsep)
			i++;
		if (s[i] && s[i] != charsep)
		{
			nb_word++;
			word_start = i;
			while (s[i] && s[i] != charsep)
				i++;
			res[nb_word] = make_tab(s, word_start, i);
			if (res[nb_word] == NULL)
				return (free_tab(res, nb_word + 1));
		}
	}
	return (res);
}
