/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:10:08 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/06 16:13:41 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"

typedef struct s_cmd
{
	char	**args;
	int		infile;
	int		outfile;
    struct s_cmd	*next;
}			t_cmd;

#endif