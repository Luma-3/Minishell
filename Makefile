# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:11:36 by jbrousse          #+#    #+#              #
#    Updated: 2024/02/28 12:36:08 by jbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
##  COMPILE	  ##
################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

################
##   LIBFT	  ##
################

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/
LIBFT_INC = $(LIBFT_DIR)includes/

#################
##   INCLUDE   ##
#################

INCLUDE_LIST	=	./includes/		\
					./$(LIBFT_INC)
INCLUDE			=	$(addprefix -I, $(INCLUDE_LIST))


#################
##   SOURCES   ##
#################

SRC_DIR				=	sources/

SRC_PARSING_DIR		=	parsing/
SRC_PARSING_LIST	=	count_word.c		\
						count_letter.c		\
						alloc_tab.c			\
						parser_utils.c		\
						parser.c
SRC_PARSING			=	$(addprefix $(SRC_PARSING_DIR), $(SRC_PARSING_LIST))

SRC_ENV_DIR			=	env/
SRC_ENV_LIST		=	transform_env.c		\
						env_utils.c
SRC_ENV				=	$(addprefix $(SRC_ENV_DIR), $(SRC_ENV_LIST))

SRC_EXEC_DIR		=	exec/
SRC_EXEC_LIST		=	get_path.c				\
						print_error_message.c	\
						handle_cmd.c			\
						exec.c				\
						verif_arg.c			\
						exec_utils.c		\
						init_child.c		\
						handle_token.c		\
						exec_command.c		\
						handle_pipe.c		\
						free.c				\
						test_access.c		\
						handle_and.c		\
						handle_or.c			
SRC_EXEC			=	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC_LIST))

SRC_BUILTINS_DIR	=	builtins/
SRC_BUILTINS_LIST	=	cd.c			\
						echo.c			\
						pwd.c			\
						unset.c
SRC_BUILTINS		=	$(addprefix $(SRC_BUILTINS_DIR), $(SRC_BUILTINS_LIST))


SRC_LIST			=	minishell.c			\
						$(SRC_PARSING)		\
						$(SRC_ENV) 			\
						$(SRC_EXEC)			\
						$(SRC_BUILTINS)
SRC					=	$(addprefix $(SRC_DIR), $(SRC_LIST))

##################
##   OBJ/NAME   ##
##################

NAME		=	minishell

NORM_LOG	:=	norme_log

OBJ_DIR		=	objects/
OBJ_LIST	=	$(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))

#################
##	 COLORS	   ##
#################

COLOR_RESET		=	\033[0m
COLOR_GREEN		=	\033[32m
COLOR_RED		=	\033[31m
COLOR_BLUE		=	\033[34m

#################
##    RULES    ##
#################



all: $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSING_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_ENV_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_BUILTINS_DIR)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	@echo "$(COLOR_BLUE)Compile $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_LIST) 
	@echo "$(COLOR_BLUE)Compile $(NAME)$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJ_LIST) $(LIBFT) -o $(NAME) -lreadline -lcurses

clean:
	@echo "$(COLOR_RED)Delete objects$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR) $(NORM_LOG)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	@echo "$(COLOR_RED)Delete $(NAME)$(COLOR_RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_DIR)

norme:
	@echo "$(COLOR_BLUE)Norminette...$(COLOR_RESET)"
	@norminette $(SRC) $(INCLUDES) $(LIBFT_DIR) > $(NORM_LOG) ; \
	if grep -q "Error" $(NORM_LOG); then \
		echo "$(COLOR_RED)Norme : KO!$(COLOR_RESET)"; \
	else \
		echo "$(COLOR_GREEN)Norme : OK!$(COLOR_RESET)"; \
	fi; \

re: fclean all

.PHONY: all clean fclean re norme