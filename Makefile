# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:11:36 by jbrousse          #+#    #+#              #
#    Updated: 2024/04/14 15:12:40 by jbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
##  COMPILE	  ##
################

CC = cc
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

COMP_DISPLAY_DIR	=	display/
COMP_DISPLAY_LIST	=	display.c			\
						display_utils.c
COMP_DISPLAY		=	$(addprefix $(COMP_DISPLAY_DIR), $(COMP_DISPLAY_LIST))


COMP_ENV_DIR		=	env/
COMP_ENV_LIST		=	transform_env.c		\
						env_utils.c
COMP_ENV			=	$(addprefix $(COMP_ENV_DIR), $(COMP_ENV_LIST))

COMP_ERROR_DIR		=	error/
COMP_ERROR_LIST		=	error.c				\
						clear_core.c		\
						free.c				\
						print_error_msg.c
COMP_ERROR			=	$(addprefix $(COMP_ERROR_DIR), $(COMP_ERROR_LIST))

COMP_HISTORY_DIR	=	history/
COMP_HISTORY_LIST	=	handle_history.c 
COMP_HISTORY		=	$(addprefix $(COMP_HISTORY_DIR), $(COMP_HISTORY_LIST))

COMP_REDIR_DIR		=	redirection/
COMP_REDIR_LIST		=	opener_kikidoc.c 	\
						init_kikidoc.c		\
						open_redir.c		\
						redir_utils.c		\
						pipe_redir.c
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
SRC_BUILTINS_LIST	=	bin_cd.c			\
						cd_utils.c			\
						bin_echo.c			\
						bin_env.c			\
						bin_exit.c			\
						exit_utils.c		\
						bin_export.c		\
						export_utils.c		\
						bin_history.c		\
						bin_pwd.c			\
						bin_unset.c			\
						builtins.c
SRC_BUILTINS		=	$(addprefix $(SRC_BUILTINS_DIR), $(SRC_BUILTINS_LIST))



SRC_EXEC_DIR		=	execution/
SRC_EXEC_LIST		=	exec_builtins.c		\
						exec_std.c			\
						exec_subshell.c		\
						read_ats.c			\
						exec_command.c		\
						get_path.c			\
						pipe_utils.c		\
						utils_exec.c
SRC_EXEC			=	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC_LIST))

SRC_PARSER_DIR		=	parser/

PRE_PARSER_DIR		=	pre_parser/
PRE_PARSER_LIST		=	verif_prompt.c		\
						verif_utils.c		\
						verif_utils2.c		
PRE_PARSER			=	$(addprefix $(PRE_PARSER_DIR), $(PRE_PARSER_LIST))

ATS_DIR				=	atomize/
ATS_LIST			=	atomizer.c			\
						atomizer_copy.c		\
						bin_tree.c			\
						bin_tree_utils.c 	\
						take_redir.c
ATS					=	$(addprefix $(ATS_DIR), $(ATS_LIST))

POST_PARSER_DIR		=	late_parser/

ALL_EXPAND_DIR		=	all_expansion/
ALL_EXPAND_LIST		= 	all_exp.c			\
						get_infos.c			\
						find_files.c		\
						decision.c			\
						open_files.c		\
						utils.c				\
						lst_utils.c			
ALL_EXPAND			=	$(addprefix $(ALL_EXPAND_DIR), $(ALL_EXPAND_LIST))

EXPAND_DIR			=	expansion/
EXPAND_LIST			=	expansion.c 		\
						env_exp.c			\
						tilde_exp.c			\
						$(ALL_EXPAND)
EXPAND				=	$(addprefix $(EXPAND_DIR), $(EXPAND_LIST))

POST_PARSER_LIST	=	late_parser.c		\
						alloc_tab.c			\
						count_utils.c		\
						clean_quote.c		\
						$(EXPAND)
POST_PARSER			=	$(addprefix $(POST_PARSER_DIR), $(POST_PARSER_LIST))

SRC_PARSER_LIST		=	parser.c			\
						is_type.c			\
						is_type2.c			\
						place_cursor.c		\
						check_char.c		\
						$(ATS)				\
						$(POST_PARSER)		\
						$(PRE_PARSER)
SRC_PARSER			=	$(addprefix $(SRC_PARSER_DIR), $(SRC_PARSER_LIST))

SRC_LIST			=	minishell.c			\
						minishell_utils.c	\
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
COLOR_GREEN		=	\033[38;5;76m
COLOR_RED		=	\033[38;5;160m
COLOR_BLUE		=	\033[38;5;45m
COLOR_ORANGE	=	\033[38;5;220m
BOLD			=	\033[1m
UNDERLINE		=	\033[4m

################
##	PROGRESS  ##
################

COMPILED_SRCS		:=	1

TOTAL_SRCS			:=	$(words $(SRC))


MAX_PATH_LENGTH 	:=	$(shell find $(SRC_DIR) -name '*.c' | awk '{print length}' | sort -nr | head -n1)
MAX_NAME_LENGTH 	:=	$(shell find $(SRC_DIR) -name '*.c' -exec basename {} \; | awk '{ print length }' | sort -nr | head -n1)

define progress_bar
	printf "$(COLOR_BLUE)Compiling: [$(COLOR_GREEN)"; \
	for i in $$(seq 1 $(4)); do \
		if [ $$i -le $$(($(1)*$(4)/$(2))) ]; then \
			printf "#"; \
		else \
			printf "."; \
		fi; \
	done; \
	printf "$(COLOR_BLUE)] $(BOLD)$(1)/$(2) $(COLOR_GREEN)$(3)$(COLOR_RESET)\r"
endef

define print_progress
	@$(eval WIDTH := $(shell tput cols))
	@$(eval LEN := $(shell expr $(WIDTH) - $(MAX_PATH_LENGTH) - 26))
	
	@printf "\033[2K"; \
	if [ $(LEN) -le 10 ]; then \
		printf "$(COLOR_BLUE)Compiling: $(BOLD)$(1)/$(2)$(COLOR_RESET)$(COLOR_GREEN) $(notdir $(3))$(COLOR_RESET)\r"; \
	else \
		$(call progress_bar,$(1),$(2),$(3),$(LEN)); \
	fi
endef

#################
##    RULES    ##
#################

all: $(LIBFT) $(STACKFT) $(NAME)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(STACKFT):
	@make -sC $(STACKFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

	@$(eval COMPILED_SRCS=$(shell expr $(COMPILED_SRCS) + 1))
	@$(call print_progress,$(COMPILED_SRCS),$(TOTAL_SRCS), $<)


$(NAME): $(call $(RQ_SRC)) $(OBJ_LIST)
	@echo "\033[2K$(COLOR_ORANGE)$(BOLD)Compilation complete ! $(COLOR_BLUE)Minishell is Ready !$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $^ $(INCLUDE) $(LIBFT) $(STACKFT) -o $@ -lreadline -lcurses

clean:
	@echo "$(COLOR_RED)$(BOLD)Delete $(NAME) objects$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR) $(NORM_LOG)
	@make clean -sC $(LIBFT_DIR)
	@make clean -sC $(STACKFT_DIR)

fclean: clean
	@echo "$(COLOR_RED)$(BOLD)Delete Minishell$(COLOR_RESET)"
	@rm -f $(NAME)
	@echo "$(COLOR_RED)$(BOLD)Delete Libft$(COLOR_RESET)"
	@rm -f $(LIBFT)
	@echo "$(COLOR_RED)$(BOLD)Delete Stackft$(COLOR_RESET)"
	@rm -f $(STACKFT)

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