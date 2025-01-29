# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbanchon <jbanchon@student42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 14:08:51 by leaugust          #+#    #+#              #
#    Updated: 2025/01/28 13:51:06 by jbanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror 

SRC			=	minishell/main.c

OBJ			=	$(SRC:.c=.o)
LIBFTDIR 	=	libft

ROSE		=	\033[1;38;5;206m
LILA		=	\033[1;38;5;177m
NC			=	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(LILA)COMPILATION DE MINISHELL$(NC)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(ROSE)MINISHELL CRÉÉ$(NC)"

clean:
	@echo "$(LILA)SUPPRESSION DES OBJECTS DANS MINISHELL$(NC)"
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "$(ROSE)DONE$(NC)"

fclean: clean
	@echo "$(LILA)SUPPRESSION DE L'EXÉCUTABLE DE MINISHELL$(NC)"
	@rm -f $(NAME)
	@echo "$(ROSE)DONE$(NC)"

re: fclean all

.PHONY: all clean fclean re