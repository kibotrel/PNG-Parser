# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 16:29:02 by kibotrel          #+#    #+#              #
#    Updated: 2019/09/25 18:06:40 by kibotrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------- VARIABLES ---------------------------------#

# Executable / Library (Can be changed).

Z				= libz.a
FT				= libft.a
NAME			= libpng.a

# Color codes (Can be changed).

RESET			= \033[0m
GREEN			= \033[32m
YELLOW			= \033[33m

#--------------------------------- DIRECTORIES  -------------------------------#

# Libraries (Can be changed).

LZ_DIR			= $(HOME)/.brew/opt/zlib/lib
LFT_DIR			= ../libft

# Project (Can be changed).

SRCS_DIR		= srcs
OBJS_DIR		= objs

# Location of all header files used in the project to avoid
# writing the full path upon include (Can be changed).

INCS_DIR		:= incs
INCS_DIR		+= ../libft/incs
INCS_DIR		+= $(HOME)/.brew/opt/zlib/include

# All the subdirectories used in the project
# to organise source files (Can be changed).

OBJS_SUBDIRS	:= core
OBJS_SUBDIRS	+= setup
OBJS_SUBDIRS	+= utils
OBJS_SUBDIRS	+= chunks

#------------------------------------ FILES -----------------------------------#

# Every libraries needed to compile the project (Can be changed).

LZ				= $(LZ_DIR)/$(Z)
LFT				= $(LFT_DIR)/$(FT)

# Used header at each compilation to check file integrity (Can be changed).

INCS			:= incs/png.h
INCS			+= incs/macros.h

# Source files (Can be changed)

SRCS			:= core/selector.c
SRCS			+= core/png_to_array.c
SRCS			+= setup/setup.c
SRCS			+= utils/maths.c
SRCS			+= utils/errors.c
SRCS			+= utils/display.c
SRCS			+= utils/filters.c
SRCS			+= chunks/end.c
SRCS			+= chunks/time.c
SRCS			+= chunks/image.c
SRCS			+= chunks/header.c
SRCS			+= chunks/signature.c

#-------------------------------- MISCELANEOUS --------------------------------#

# Some tricks in order to get the makefile doing his job (Can't be changed).

D_SRCS			= $(addsuffix /, $(SRCS_DIR))
D_OBJS			= $(addsuffix /, $(OBJS_DIR))
C_OBJS			= $(addprefix $(D_OBJS), $(OBJS))
C_INCS			= $(foreach include, $(INCS_DIR), -I$(include))
C_SUBDIRS		= $(foreach dir, $(OBJS_SUBDIRS), $(D_OBJS)$(dir))

#--------------------------------- COMPILATION --------------------------------#

# How files should be compiled (Can't be changed).

CC				= gcc
OBJS			= $(SRCS:.c=.o)

# Linked libraries at compile time (Can be changed).

LIBS			:= -L$(LFT_DIR) -lft
LIBS			+= -L$(LZ_DIR) -lz

# Compilation flags (Can be changed).

CFLAGS			= $(C_INCS) -Wall -Wextra -Werror -O3

#------------------------------------ RULES -----------------------------------#

# Redefinition of the implicit compilation rule
# to prompt some informations (Can't be changed).

$(D_OBJS)%.o: $(D_SRCS)%.c $(INCS)
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Implicit make rule simply using dependancies
# to compile our project (Can't be canged).

all: $(C_SUBDIRS) $(NAME)

$(NAME): $(LZ) $(LFT) $(OBJS_DIR) $(C_OBJS)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@ar rcs $(NAME) $(C_OBJS)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

# Libraries installation using brew without prompting
# anything on standard output (Can be changed).

$(LZ):
	@echo "$(GREEN)***   Installing library $(Z)  ...  ***\n$(RESET)"
	@brew install zlib > /dev/null 2>&1

# Libraries installion using their own Makefile (Can be changed).

$(LFT):
	@make -sC $(LFT_DIR) -j

# Rules used to create folders if they aren't already existing (Can be changed).

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(C_SUBDIRS):
	mkdir -p $(C_SUBDIRS)

# Deleting all .o files. (Can't be changed).

clean:
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(C_OBJS)

# Deleting all executables and libraries after cleaning up
# all .o files (Can't be changed).

fclean: clean
	@echo "$(GREEN)***   Deleting library $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(NAME)
	@if [ -f "$(LZ)" ]; then													\
		echo "$(GREEN)***   Deleting library $(Z)   ...  ***\n$(RESET)";		\
		brew uninstall zlib > /dev/null 2>&1;									\
	fi

# Re-compile everything (Can't be changed).

re: fclean all

# Avoid unexpected behaviour when regular files
# get the same name as the following variables (Can be changed).

.PHONY: all clean fclean re
