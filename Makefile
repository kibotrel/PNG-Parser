# Executable's name (Can be changed)

NAME		= png-to-bmp

# All the directories needed to know where files should be (Can be changed)

OBJDIR		= objs/
OBJSUBDIRS	= core setup utils chunks
SRCDIR		= srcs/
LFTDIR		= ./libft/
INCDIR		= ./incs/ ./libft/incs/

# Source files (Can be changed)

SRC			= main.c				\
			  setup/setup.c			\
			  chunks/header.c		\
			  chunks/end.c			\
			  chunks/signature.c	\
			  core/png_to_bmp.c		\
			  utils/clean.c			\
			  utils/maths.c

LFT			= ./libft/libft.a

# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
SUBDIRS		= $(foreach dir, $(OBJSUBDIRS), $(OBJDIR)$(dir))
INCLUDES	= $(foreach include, $(INCDIR), -I$(include))

# How files should be compiled with set flags (Can be changed)

CC			= gcc
OBJ			= $(SRC:.c=.o)
LIBS		= -L$(LFTDIR) -lft
CFLAGS		= $(INCLUDES) -Wall -Wextra -Werror

# Color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libft and then the Project

all: $(SUBDIRS) $(NAME)

$(NAME): $(LFT) $(OBJDIR) $(COBJ)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@$(CC) -o $(NAME) $(COBJ) $(LIBS)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(SUBDIRS):
	@mkdir -p $(SUBDIRS)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation rule for function library "libft"

$(LFT):
	@make -sC $(LFTDIR)

# Deleting all .o files and then the directory where they were located

clean:
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(COBJ)

# Deleting the executable after cleaning up all .o files

fclean: clean
	@make -sC $(LFTDIR) fclean
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
