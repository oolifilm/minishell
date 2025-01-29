/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:46:16 by julien            #+#    #+#             */
/*   Updated: 2024/05/23 16:40:30 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int character)
{
	if (((character >= 'A' && character <= 'Z') || (character >= 'a'
				&& character <= 'z')) || (character >= '0' && character <= '9'))
		return (1);
	return (0);
}
