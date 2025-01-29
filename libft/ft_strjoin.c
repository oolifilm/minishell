/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:18:31 by jbanchon          #+#    #+#             */
/*   Updated: 2024/05/29 14:35:05 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*len_final;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	len_final = (char *)malloc(sizeof(char) * (size + 1));
	if (len_final == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		len_final[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		len_final[i] = s2[j];
		i++;
		j++;
	}
	len_final[i] = '\0';
	return (len_final);
}
