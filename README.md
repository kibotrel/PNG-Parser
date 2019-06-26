# PNG-Parser
[![CodeFactor](https://www.codefactor.io/repository/github/kibotrel/png-parser/badge)](https://www.codefactor.io/repository/github/kibotrel/png-parser) [![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

This project is made to parse and load PNG [(Portable Network Graphics)](https://en.wikipedia.org/wiki/Portable_Network_Graphics) files using this small library (and [zlib](https://github.com/madler/zlib) to uncompress data streams).

## Install

This should be fully portable (tested on **macOS Sierra 10.12.6** and **Debian Stretch 9.8**).

In order to use this PNG loader in another project, **libft.a**, another library of mine is required. Here is the install process :
```shell
$> git clone https://github.com/kibotrel/42-Libft libft
$> git clone --recurse-submodules https://github.com/kibotrel/PNG-Parser libpng
$> make -C libft && make -C libpng
```

You'll get a static library called **libpng.a** at the root of **libpng** folder. In order to use it afterwards you may have to include it to the compilation when you call any function of the library in another project.
```shell
$> gcc -I./libft/incs -I./libpng/incs/ -L./libft/ -lft -L./libpng/ -lpng [...]
```

This process can be automated using **Makefile** in the parent folder of these two libraries as folowing :
```Makefile
# All the directories needed to know where files should be.

ZLIB_DIR	= libpng/ZLIB/lib/
INCS_DIR	= ./libft/incs/ ./libpng/incs/ [...]
LIBFT_DIR	= libft/
LIBPNG_DIR	= libpng/

# The two different libraries.

LFT     = ./libft/libft.a
LPNG    = ./libpng/libpng.a


# Setup compilation arguments.

CC      = gcc
LIBS    = -L$(LFTDIR) -lft -L$(LPNGDIR) -lpng -L./$(LZDIR) -lz [...]
CFLAGS  = $(INCLUDES) -Wall -Wextra -Werror [...]
INCLUDE = $(foreach include, $(INCDIR), -I$(include))

# Compile the two libraries (+zlib) and then compile the main project where png_to_array() is used.

all: $(LFT) $(LPNG)
	$(CC) $(CFLAGS) $(LIBS) [...]

# Dependencies of rule all, compile each library.

$(LFT):
	make -C $(LFTDIR) -j

$(LPNG):
	make -C $(LPNGDIR) -j
```

The given example isn't complete, '[...]' represent the parts you need to fill with your sources files / extra flags or libraries in order to compile your main project correctly.

## Usage
### Prototype
