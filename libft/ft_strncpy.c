/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:24:14 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 10:25:07 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
    size_t	i;

    i = 0;
    while (i < len)
    {
        dest[i] = src[i];
        i++;
    }
    while (i < len)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}
