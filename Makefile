# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:11:36 by jbrousse          #+#    #+#              #
#    Updated: 2024/04/02 13:34:25 by antgabri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
##  COMPILE	  ##
################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

################
##   LIBS	  ##
################

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libs/libft/
LIBFT_INC = $(LIBFT_DIR)includes/

STACKFT = $(STACKFT_DIR)stackft.a
STACKFT_DIR = libs/stackft/
STACKFT_INC = $(STACKFT_DIR)includes/

#################
##   INCLUDE   ##
#################

INCLUDE_LIST	=	./includes/				\
					./includes/components/	\
					./$(LIBFT_INC) 			\
					./$(STACKFT_INC)
INCLUDE			=	$(addprefix -I, $(INCLUDE_LIST))


#######################
##   SOURCES FILES   ##
#######################

SRC_DIR				=	sources/


########################
##   COMPONENTS SRC   ##
########################

COMP_DISPLAY_DIR		=	display/
COMP_DISPLAY_LIST	=	display.c			\
						display_utils.c
COMP_DISPLAY			=	$(addprefix $(COMP_DISPLAY_DIR), $(COMP_DISPLAY_LIST))


COMP_ENV_DIR			=	env/
COMP_ENV_LIST		=	transform_env.c		\
						env_utils.c
COMP_ENV				=	$(addprefix $(COMP_ENV_DIR), $(COMP_ENV_LIST))

COMP_ERROR_DIR		=	error/
COMP_ERROR_LIST		=	error.c				\
						clear_ats.c			\
						error_utils.c		\
						print_error_msg.c
COMP_ERROR			=	$(addprefix $(COMP_ERROR_DIR), $(COMP_ERROR_LIST))

COMP_HISTORY_DIR		=	history/
COMP_HISTORY_LIST	=	handle_history.c 
COMP_HISTORY			=	$(addprefix $(COMP_HISTORY_DIR), $(COMP_HISTORY_LIST))

COMP_REDIR_DIR		=	redirection/
COMP_REDIR_LIST		=	heredoc.c 			\
						open_redir.c		\
						redir_utils.c
COMP_REDIR			=	$(addprefix $(COMP_REDIR_DIR), $(COMP_REDIR_LIST))

COMP_SIGNAL_DIR		=	signal/
COMP_SIGNAL_LIST		=	signal.c
COMP_SIGNAL			=	$(addprefix $(COMP_SIGNAL_DIR), $(COMP_SIGNAL_LIST))


COMPONENTS_DIR		=	components/

COMPONENTS_LIST		=	$(COMP_DISPLAY)		\
						$(COMP_ENV)			\
						$(COMP_ERROR)		\
						$(COMP_HISTORY)		\
						$(COMP_REDIR)		\
						$(COMP_SIGNAL)
COMPONENTS			=	$(addprefix $(COMPONENTS_DIR), $(COMPONENTS_LIST))

##----------------------------------------------------------------------------------##
##									SOURCES PARTS									##
##----------------------------------------------------------------------------------##


SRC_BUILTINS_DIR	=	builtins/
SRC_BUILTINS_LIST	=	bin_cd.c		\
						bin_echo.c		\
						bin_env.c		\
						bin_exit.c		\
						bin_export.c	\
						bin_pwd.c		\
						bin_unset.c		\
						builtins.c
SRC_BUILTINS		=	$(addprefix $(SRC_BUILTINS_DIR), $(SRC_BUILTINS_LIST))



SRC_EXEC_DIR		=	execution/
SRC_EXEC_LIST		=	exec_std.c			\
						exec_subshell.c		\
						read_ats.c			\
						exec_command.c		\
						get_path.c			\
						pipe_utils.c
SRC_EXEC			=	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC_LIST))

SRC_PARSER_DIR		=	parser/

PRE_PARSER_DIR		=	pre_parser/
PRE_PARSER_LIST		=	verif_prompt.c			\
						verif_utils.c			\
						verif_utils2.c		
PRE_PARSER			=	$(addprefix $(PRE_PARSER_DIR), $(PRE_PARSER_LIST))

ATS_DIR				=	atomize/
ATS_LIST			=	atomizer.c				\
						atomizer_copy.c			\
						bin_tree.c				\
						bin_tree_utils.c 		\
						take_redir.c
ATS					=	$(addprefix $(ATS_DIR), $(ATS_LIST))

POST_PARSER_DIR		=	late_parser/

ALL_EXPAND_DIR		=	all_expansion/
ALL_EXPAND_LIST		= 	all_exp.c			\
						all_utils.c
ALL_EXPAND			=	$(addprefix $(ALL_EXPAND_DIR), $(ALL_EXPAND_LIST))

EXPAND_DIR			=	expansion/
EXPAND_LIST			=	expansion.c 			\
						env_exp.c				\
						tilde_exp.c			\
						$(ALL_EXPAND)
EXPAND				=	$(addprefix $(EXPAND_DIR), $(EXPAND_LIST))

POST_PARSER_LIST	=	late_parser.c			\
						alloc_tab.c				\
						count_utils.c			\
						clean_quote.c			\
						$(EXPAND)
POST_PARSER			=	$(addprefix $(POST_PARSER_DIR), $(POST_PARSER_LIST))

SRC_PARSER_LIST		=	parser.c			\
						is_type.c			\
						is_type2.c			\
						place_cursor.c		\
						place_cursor2.c		\
						$(ATS)				\
						$(POST_PARSER)		\
						$(PRE_PARSER)
SRC_PARSER			=	$(addprefix $(SRC_PARSER_DIR), $(SRC_PARSER_LIST))

SRC_LIST			=	minishell.c			\
						safe_mode.c			\
						init_shell.c		\
						$(COMPONENTS)		\
						$(SRC_BUILTINS)		\
						$(SRC_PARSER)		\
						$(SRC_EXEC)
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



all: $(LIBFT) $(STACKFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)$(COMP_DISPLAY_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)$(COMP_ENV_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)$(COMP_ERROR_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)$(COMP_HISTORY_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)$(COMP_REDIR_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPONENTS_DIR)$(COMP_SIGNAL_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_BUILTINS_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(ATS_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(POST_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(POST_PARSER_DIR)$(EXPAND_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(POST_PARSER_DIR)$(EXPAND_DIR)$(ALL_EXPAND_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(PRE_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_HISTORY_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_REDIR_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_SIGNAL_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_ERROR_DIR)
	

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(STACKFT):
	@make -sC $(STACKFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(COLOR_BLUE)Compile $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_LIST)
	@echo "$(COLOR_BLUE)Compile $(NAME)$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJ_LIST) $(LIBFT) $(STACKFT) -o $(NAME) -lreadline -lcurses

clean:
	@echo "$(COLOR_RED)Delete objects$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR) $(NORM_LOG)
	@make clean -sC $(LIBFT_DIR) 
	@make clean -sC $(STACKFT_DIR)

fclean: clean
	@echo "$(COLOR_RED)Delete $(NAME)$(COLOR_RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_DIR) 
	@make fclean -sC $(STACKFT_DIR)

norme:
	@echo "$(COLOR_BLUE)Norminette...$(COLOR_RESET)"
	@norminette $(SRC) $(INCLUDES) $(LIBFT_DIR) $(STACKFT_DIR) > $(NORM_LOG) ; \
	if grep -q "Error" $(NORM_LOG); then \
		echo "$(COLOR_RED)Norme : KO!$(COLOR_RESET)"; \
	else \
		echo "$(COLOR_GREEN)Norme : OK!$(COLOR_RESET)"; \
	fi; \

re: fclean all

.PHONY: all clean fclean re norme