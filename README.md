# PNG-Parser
[![CodeFactor](https://www.codefactor.io/repository/github/kibotrel/png-parser/badge)](https://www.codefactor.io/repository/github/kibotrel/png-parser) [![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

This project is made to parse and load PNG [(Portable Network Graphics)](https://en.wikipedia.org/wiki/Portable_Network_Graphics) files using this small library (and [zlib](https://github.com/madler/zlib) to inflate data streams) under a MIT License.

## Install

This should be fully portable (tested on **macOS Sierra 10.12.6** and **Debian Stretch 9.8**). In order to use this PNG loader in another project, **libft.a**, [another library of mine](https://github.com/kibotrel/42-Libft) is required. Here is the install process :
```shell
$> git clone https://github.com/kibotrel/42-Libft libft
$> git clone --recurse-submodules https://github.com/kibotrel/PNG-Parser libpng
$> make -C libft && make -C libpng
```

You will get a static library called **libpng.a** at the root of **libpng** folder. In order to use it afterwards you may have to include it to the compilation when you call any function of the library in another project.
```shell
$> gcc -I./libft/incs -I./libpng/incs/ -L./libft/ -lft -L./libpng/ -lpng [...]
```

This process can be automated using a **Makefile** in the parent folder of these two libraries as folowing :
```Makefile
# All the directories needed to know where files should be.

LZ_DIR   = libpng/ZLIB/lib/
LFT_DIR  = libft/
INCS_DIR = ./libft/incs/ ./libpng/incs/ [...]
LPNG_DIR = libpng/

# The two different libraries.

LFT     = ./libft/libft.a
LPNG    = ./libpng/libpng.a


# Setup compilation arguments.

CC       = gcc
LIBS     = -L$(LFT_DIR) -lft -L$(LPNG_DIR) -lpng -L./$(LZ_DIR) -lz [...]
CFLAGS   = $(INCLUDES) -Wall -Wextra -Werror [...]
INCLUDES = $(foreach include, $(INCS_DIR), -I$(include))

# Compile the two libraries (+zlib) and then compile the main project where png_to_array() is used.

all: $(LFT) $(LPNG)
	$(CC) $(CFLAGS) $(LIBS) [...]

# Dependencies of rule all, compile each library.

$(LFT):
	make -C $(LFTDIR) -j

$(LPNG):
	make -C $(LPNGDIR) -j

[...]
```

The given example isn't complete, '[...]' represent the parts you need to fill with your sources files / extra flags or libraries in order to compile your main project correctly upon `make`.

## Usage
### Prototype
The only function that should be used from this library is :
```C
#include "png.h"
#include "macros.h"

int     png_to_array(char *path, t_png *image, int flag);
```

This function returns `0` if the process ended correctly, a particular error-code (documented bellow) is returned. Said header files `png.h` and `macros.h` are located in `./incs/`. Type `t_png` is defined as follow :
```C
typedef struct      s_png
{
    int             width;
    int             height;
    unsigned int    *pixels;
}                   t_png;
```
### Breakdown

Quick explanation on each parameter and how they are supposed to be used...

Parameter | Description | Possible value
:---: | :---: | :---:
`path` | file's path that the function will parse | Only paths followed by ".png" could be a correct input depending on the informations stored in its [IHDR Chunk](https://www.w3.org/TR/2003/REC-PNG-20031110/#11IHDR) handled on the current version of the parser.
`image` | Where informations related to the given PNG would be stored at the end process | Any pointer is a valid value, however be careful, the given structure will be passed through a [bzero()](http://man7.org/linux/man-pages/man3/bzero.3.html) at the beginning of the parsing process no matter what happens after, this pointer will be updated and could be used afterwards in the process ended correctly otherwise it would be a **NULL** pointer.
`flag` | Used to display informations during the parsing process | Two values are handled others are simply ignored and considered as `0` (normal mode). `1` or **VERBOSE** macro available in `macros.h` allow the user to see what is stored in each handled chunks then [uncompressing](https://www.w3.org/TR/2003/REC-PNG-20031110/#10Compression) and [unfiltering](https://www.w3.org/TR/2003/REC-PNG-20031110/#9Filters) processes in [IDAT Chunks](https://www.w3.org/TR/2003/REC-PNG-20031110/#11IDAT). `2` or **DEBUG** macro available in the same file allow the user to get more informations about the file structure. Aside of this it prompts in which chunk and which error was trigger at the exit or `0` if everything went well.

### Error management
Each following error is handled by the program leading to a complete memory free :

* Failed memory allocation (*ERROR-CODE 1*)
* Failed to open the given file (*ERROR-CODE 2*)
* Invalid file signature (*ERROR-CODE 3*)
* Incorrect IHDR chunk composition (*ERROR-CODE 4*)
* Invalid iamge dimensions (*ERROR-CODE 5*)
* File size not handled (*ERROR-CODE 6*)
* Incorrect bit depth (*ERROR-CODE 7*)
* Incorrect color-type (*ERROR-CODE 8*)
* Wrong pressets depth and color-type (*ERROR-CODE 9*)
* Incorrect [IEND chunk](https://www.w3.org/TR/2003/REC-PNG-20031110/#11IEND) composition (*ERROR-CODE 10*)
* Invalid file structure (*ERROR-CODE 11*)
* Incorrect [tIME chunk](https://www.w3.org/TR/2003/REC-PNG-20031110/#11tIME) (*ERROR-CODE 12*)
* Misformated file date (*ERROR-CODE 13*)
* Incorrect IDAT chunk composition (*ERROR-CODE 14*)
* Settings not handled by the parsing (*ERROR-CODE 15*)
* Failed to read the given file (*ERROR-CODE 16*)
* Corrupted or invalid image data (*ERROR-CODE 17*)
* Unable to close the given file (*ERROR-CODE 18*)

Whenever one of these error occurs, the correct error message is displayed on the standard output and the parser returns an error code that you can retrieve.

### Example

Here is a valid implementation of `png_to_array()` :
```C
#include "png.h"
#include "macros.h"

{
    t_png   image;

    [...]
    if (png_to_array("file.png", &image, DEBUG))
    {
        // Do stuff when an error is triggered.
    }
    else
    {
        // Do stuff when the file is correctly parsed.
    }
    [...]
}
```
