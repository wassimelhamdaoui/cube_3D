/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:30:45 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/20 17:48:13 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_wordlen(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(const char *s, char spl)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == spl)
			i++;
		if (s[i] != '\0')
			k++;
		while (s[i] && s[i] != spl)
			i++;
	}
	return (k);
}

static void	ft_inits(int *i, int *k)
{
	*i = -1;
	*k = -1;
}

static void	ft_free(char **spl)
{
	int	j;

	j = -1;
	while (spl[++j])
		free(spl[j]);
	free(spl);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**spl;
	int		k;

	ft_inits(&i, &k);
	if (!s)
		return (NULL);
	spl = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!spl)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
		{
			spl[++k] = ft_substr(s, i, ft_wordlen(s + i, c));
			if (!spl[k])
			{
				ft_free(spl);
				return (NULL);
			}
			i = i + ft_wordlen(s + i, c) - 1;
		}
	}
	spl[++k] = NULL;
	return (spl);
}
