# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:11:36 by jbrousse          #+#    #+#              #
#    Updated: 2024/03/22 14:48:34 by antgabri         ###   ########.fr        #
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

# SRC_BUILTINS_DIR	=	builtins/
# SRC_BUILTINS_LIST	=	bin_cd.c		\
# 						bin_echo.c		\
# 						bin_env.c		\
# 						bin_exit.c		\
# 						bin_export.c	\
# 						bin_pwd.c		\
# 						bin_unset.c		\
# 						builtins.c		\
# 						echo_utils.c
# SRC_BUILTINS		=	$(addprefix $(SRC_BUILTINS_DIR), $(SRC_BUILTINS_LIST))

SRC_DISPLAY_DIR		=	display/
SRC_DISPLAY_LIST	=	presentation_display.c		\
						presentation_position.c		\
						display_utils.c
SRC_DISPLAY			=	$(addprefix $(SRC_DISPLAY_DIR), $(SRC_DISPLAY_LIST))


SRC_ENV_DIR			=	env/
SRC_ENV_LIST		=	transform_env.c		\
						env_utils.c
SRC_ENV				=	$(addprefix $(SRC_ENV_DIR), $(SRC_ENV_LIST))


SRC_NEW_EXEC_DIR	=	new_exec/
SRC_NEW_EXEC_LIST	=	exec_std.c			\
						exec_subshell.c		\
						read_ats.c			\
						exec_command.c		\
						get_path.c			\
						exec_pipe.c			
SRC_NEW_EXEC		=	$(addprefix $(SRC_NEW_EXEC_DIR), $(SRC_NEW_EXEC_LIST))

SRC_PARSER_DIR			=	parser/

SRC_PRE_PARSER_DIR		=	pre_parser/
SRC_PRE_PARSER_LIST		=	verif_arg.c			
SRC_PRE_PARSER			=	$(addprefix $(SRC_PRE_PARSER_DIR), $(SRC_PRE_PARSER_LIST))

SRC_ATS_DIR				=	ats/
SRC_ATS_LIST			=	ats.c				\
							ats_copy_cmd.c		\
							bin_tree.c			\
							bin_tree_utils.c 	\
							take_redir.c		
SRC_ATS					=	$(addprefix $(SRC_ATS_DIR), $(SRC_ATS_LIST))

SRC_POST_PARSER_DIR		=	post_parser/
SRC_POST_PARSER_LIST	=	post_parser.c		\
							alloc_tab.c			\
							count_utils.c		\
							clean_quote.c
SRC_POST_PARSER			=	$(addprefix $(SRC_POST_PARSER_DIR), $(SRC_POST_PARSER_LIST))

SRC_PARSER_LIST			=	is_type.c			\
							is_type2.c			\
							place_cursor.c		\
							$(SRC_ATS)			\
							$(SRC_POST_PARSER)	\
							$(SRC_PRE_PARSER)
SRC_PARSER				=	$(addprefix $(SRC_PARSER_DIR), $(SRC_PARSER_LIST))


SRC_HISTORY_DIR		=	history/
SRC_HISTORY_LIST	=	handle_history.c 
SRC_HISTORY			=	$(addprefix $(SRC_HISTORY_DIR), $(SRC_HISTORY_LIST))

SRC_REDIR_DIR		=	redirection/
SRC_REDIR_LIST		=	heredoc.c \
						open_redir.c
SRC_REDIR			=	$(addprefix $(SRC_REDIR_DIR), $(SRC_REDIR_LIST))

				
SRC_SIGNAL_DIR		=	signal/
SRC_SIGNAL_LIST		=	signal.c
SRC_SIGNAL			=	$(addprefix $(SRC_SIGNAL_DIR), $(SRC_SIGNAL_LIST))

SRC_LIST			=	minishell.c				\
						print_error_msg.c		\
						test_access.c			\
						clear_ats.c				\
						$(SRC_BUILTINS)			\
						$(SRC_DISPLAY)			\
						$(SRC_PARSER)			\
						$(SRC_ENV) 				\
						$(SRC_NEW_EXEC)			\
						$(SRC_HISTORY)		\
						$(SRC_REDIR)		\
						$(SRC_SIGNAL)
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
	@mkdir -p $(OBJ_DIR)$(SRC_DISPLAY_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_ENV_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_EXEC_DIR)$(SRC_TOKEN_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_NEW_EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(SRC_ATS_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(SRC_POST_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_PARSER_DIR)$(SRC_PRE_PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_HISTORY_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_REDIR_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_SIGNAL_DIR)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
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