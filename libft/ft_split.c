/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:17:59 by jbanchon          #+#    #+#             */
/*   Updated: 2024/05/30 12:27:02 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != delim && (i == 0 || s[i - 1] == delim))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_extract_word(const char **s, char delim)
{
	const char	*start;
	size_t		len;
	char		*word;

	while (**s == delim && **s != '\0')
		(*s)++;
	if (**s == '\0')
		return (NULL);
	start = *s;
	len = 0;
	while (**s != '\0' && **s != delim)
	{
		(*s)++;
		len++;
	}
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static char	**free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**words;
	int		i;

	word_count = ft_count_words(s, c);
	words = (char **)malloc((word_count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		words[i] = ft_extract_word(&s, c);
		if (words[i] == 0)
			return (free_words(words));
		i++;
	}
	words[i] = 0;
	return (words);
}
