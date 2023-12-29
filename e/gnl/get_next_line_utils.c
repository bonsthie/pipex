/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:04:48 by fparis            #+#    #+#             */
/*   Updated: 2023/11/22 16:38:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	n;
	size_t	i;

	if (!nmemb || !size)
		return (malloc(1));
	if (nmemb * size / size != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	n = nmemb * size;
	while (i < n)
	{
		*((unsigned char *)(ptr + i)) = (unsigned char) 0;
		i++;
	}
	return (ptr);
}

char	*ft_mallocat(char *src, char *new)
{
	char	*res;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	res = malloc(ft_strlen(src) + ft_strlen(new) + 1);
	while (res && src && src[i])
	{
		res[i] = src[i];
		i++;
	}
	while (res && new && new[i2])
	{
		res[i + i2] = new[i2];
		i2++;
	}
	free(src);
	if (new)
		free(new);
	if (res)
		res[i + i2] = '\0';
	return (res);
}

void	*ft_free(char **lst1, char **lst2)
{
	if (lst1 && *lst1)
	{
		free(*lst1);
		*lst1 = NULL;
	}
	if (lst2 && *lst2)
	{
		free(*lst2);
		*lst2 = NULL;
	}
	return (NULL);
}
