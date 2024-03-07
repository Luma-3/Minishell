# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:11:36 by jbrousse          #+#    #+#              #
#    Updated: 2024/03/07 11:02:04 by jbrousse         ###   ########.fr        #
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

SRC_BUILTINS_DIR	=	builtins/
SRC_BUILTINS_LIST	=	bin_cd.c		\
						bin_echo.c		\
						bin_env.c		\
						bin_exit.c		\
						bin_export.c	\
						bin_pwd.c		\
						bin_unset.c		\
						builtins.c		\
						echo_utils.c
SRC_BUILTINS		=	$(addprefix $(SRC_BUILTINS_DIR), $(SRC_BUILTINS_LIST))

SRC_ENV_DIR			=	env/
SRC_ENV_LIST		=	transform_env.c		\
						env_utils.c
SRC_ENV				=	$(addprefix $(SRC_ENV_DIR), $(SRC_ENV_LIST))

SRC_EXEC_DIR		=	exec/

SRC_TOKEN_DIR		=	token/
SRC_TOKEN_LIST		=	exec_token.c		\
						handle_and.c		\
						handle_or.c			\
						handle_pipe.c		\
						handle_std.c
SRC_TOKEN			=	$(addprefix $(SRC_TOKEN_DIR), $(SRC_TOKEN_LIST))

SRC_EXEC_LIST		=	exec_command.c		\
						exec_utils.c		\
						exec.c				\
						get_path.c			\
						$(SRC_TOKEN)
SRC_EXEC			=	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC_LIST))

SRC_NEW_PARSER_DIR	=	new_parser/
SRC_NEW_PARSER_LIST	=	bin_tree.c			\
						read_line.c			\
						read_line_utils.c	\
						ats.c
SRC_NEW_PARSER		=	$(addprefix $(SRC_NEW_PARSER_DIR), $(SRC_NEW_PARSER_LIST))

SRC_PARSING_DIR		=	parsing/
SRC_PARSING_LIST	=	alloc_tab.c			\
						count_letter.c		\
						count_word.c		\
						parser_utils.c		\
						parser.c			\
						verif_arg.c
SRC_PARSING			=	$(addprefix $(SRC_PARSING_DIR), $(SRC_PARSING_LIST))

SRC_HISTORY_DIR		=	history/
SRC_HISTORY_LIST	=	handle_history.c 
SRC_HISTORY			=	$(addprefix $(SRC_HISTORY_DIR), $(SRC_HISTORY_LIST))

SRC_REDIR_DIR		=	redirection/
SRC_REDIR_LIST		=	heredoc.c
SRC_REDIR			=	$(addprefix $(SRC_REDIR_DIR), $(SRC_REDIR_LIST))

				
SRC_SIGNAL_DIR		=	signal/
SRC_SIGNAL_LIST		=	signal.c
SRC_SIGNAL			=	$(addprefix $(SRC_SIGNAL_DIR), $(SRC_SIGNAL_LIST))

SRC_LIST			=	minishell.c			\
						print_error_msg.c	\
						test_access.c		\
						$(SRC_BUILTINS)		\
						$(SRC_PARSING)		\
						$(SRC_ENV) 			\
						$(SRC_EXEC)			\
						$(SRC_HISTORY)		\
						$(SRC_REDIR)		\
						$(SRC_SIGNAL)		\
						$(SRC_NEW_PARSER)
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
	@mkdir -p $(OBJ_DIR)$(SRC_BUILTINS_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_ENV_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_EXEC_DIR)$(SRC_TOKEN_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_NEW_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSING_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_HISTORY_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_REDIR_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_SIGNAL_DIR)

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