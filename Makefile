# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 16:29:02 by kibotrel          #+#    #+#              #
#    Updated: 2019/06/25 21:31:40 by kibotrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's name (Can be changed)

NAME		= libpng.a

# All the directories needed to know where files should be (Can be changed)

OBJDIR		= objs/
OBJSUBDIRS	= core setup utils chunks
SRCDIR		= srcs/
INCDIR        = ./incs/ ../libft/incs/ ./zlib-1.2.11/

# Some macros (Can't be changed)

ABSDIR		= $(shell pwd)
ZLIBDIR		= $(ABSDIR)/zlib-1.2.11/
LZDIR		= ZLIB/lib/
LFTDIR		= ../Documents/42-Wolf3D/libft/

# Source files (Can be changed)

INCS		= incs/macros.h incs/png.h

SRC			= setup/setup.c								\
														\
			  chunks/header.c		chunks/end.c		\
			  chunks/signature.c	chunks/time.c		\
			  chunks/image.c							\
														\
			  core/png_to_array.c	core/selector.c		\
														\
			  utils/maths.c			utils/display.c		\
			  utils/errors.c		utils/filters.c

# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
SUBDIRS		= $(foreach dir, $(OBJSUBDIRS), $(OBJDIR)$(dir))
INCLUDES	= $(foreach include, $(INCDIR), -I$(include))

# How files should be compiled with set flags (Can be changed)

CC			= gcc
OBJ			= $(SRC:.c=.o)
CFLAGS		= $(INCLUDES) -Wall -Wextra -Werror
LIBS		= -L$(LFTDIR) -lft -L$(LZDIR) -lz

# Color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libft and then the Project

all: $(SUBDIRS) ZLIB $(NAME)

ZLIB:
	@mkdir -p ZLIB
	@mkdir -p ZLIB/build
	@cd ZLIB/build;									\
	$(ZLIBDIR)configure --prefix $(ABSDIR)/ZLIB;    \
	make -j; 										\
	make install

$(NAME): $(OBJDIR) $(COBJ)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@ar rcs $(NAME) $(COBJ)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(SUBDIRS):
	@mkdir -p $(SUBDIRS)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Deleting all .o files and then the directory where they were located

clean:
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(COBJ)

# Deleting the executable after cleaning up all .o files

fclean: clean
	@rm -rf ZLIB
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
