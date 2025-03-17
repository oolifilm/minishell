/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:00:00 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/17 10:00:00 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_UTILS_H
# define FT_EXPORT_UTILS_H

int		is_valid_env_var(const char *var);
void	print_env_var(char *var);
int		compare_vars(const void *a, const void *b);
int		print_sorted_env(void);

#endif
