# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 14:08:51 by leaugust          #+#    #+#              #
#    Updated: 2025/04/09 11:05:27 by jbanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror 
LIBFTDIR 	=	libft
LDFLAGS 	=	-lreadline -L$(LIBFTDIR) -lft 

SRC			=	srcs/parsing/tokenizer/tokenizer.c \
				srcs/parsing/tokenizer/token_utils.c \
				srcs/parsing/tokenizer/token_operators.c \
				srcs/parsing/tokenizer/token_quotes.c \
				srcs/parsing/tokenizer/token_command.c \
				srcs/parsing/tokenizer/double_quoted.c \
				srcs/parsing/tokenizer/token_is_redir.c \
				srcs/parsing/parser/parsing_utils.c \
				srcs/parsing/parser/parsing.c \
				srcs/parsing/executor/exec_cmd.c \
				srcs/builtins/ft_cd.c \
				srcs/builtins/ft_echo.c \
				srcs/builtins/ft_env.c \
				srcs/builtins/ft_exit.c \
				srcs/builtins/export/ft_export.c \
				srcs/builtins/ft_pwd.c \
				srcs/builtins/ft_unset.c \
				srcs/builtins/export/ft_export_utils.c \
				srcs/builtins/export/ft_export_print.c \
				srcs/parsing/signals/signals.c \
				srcs/main.c 

OBJ 		= 	$(SRC:.c=.o)

LIBFTDIR 	=	libft
LIBFT		=	$(LIBFTDIR)/libft.a

ROSE		=	\033[1;38;5;206m
LILA		=	\033[1;38;5;177m
NC			=	\033[0m

all: $(NAME)

$(LIBFT):
	@echo "$(LILA)COMPILATION DE LA LIBFT$(NC)"
	@make -C $(LIBFTDIR) --silent
	@echo "$(ROSE)LIBFT CRÉÉ$(NC)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(LILA)COMPILATION DE MINISHELL$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "$(ROSE)MINISHELL CRÉÉ$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(LILA)SUPPRESSION DES OBJECTS DANS MINISHELL$(NC)"
	@rm -f $(OBJ)
	@echo "$(ROSE)DONE$(NC)"

fclean: clean
	@echo "$(LILA)SUPPRESSION DE L'EXÉCUTABLE DE MINISHELL$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --silent
	@echo "$(ROSE)DONE$(NC)"

re: fclean all

.PHONY: all clean fclean re