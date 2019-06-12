#ifndef PNG_H
# define PNG_H

# define MAX_SIZE	8388608

typedef struct		s_chunk
{
	int				size;
	char			name[5];
	char			length[4];
}					t_chunk;

typedef struct		s_infos
{
	int				chunk;
	int				width;
	int				height;
	int				position;
	unsigned char	color;
	unsigned char	depth;
	unsigned char	filter;
	unsigned char	interlace;
	unsigned char	compression;
}					t_infos;

typedef struct		s_control
{
	int				size;
	t_chunk			chunk;
	t_infos			info;
}					t_control;

typedef void		(*handler)(char *buffer, t_control *file);

typedef struct		s_process
{
	char			*type;
	handler			process;
}					t_process;

int					is_power_two(int nb);
int					big_endian(char *length);
void				png_to_bmp(char *png);
void				header(char *buffer, t_control *file);
void				clean(char *buffer, char *error, int code);
void				setup(t_control *file, t_process *handler);
void				fill_chunkname(char *chunk, char *buffer, int size);

# define ERR_OPEN 	"\033[31;1mError :\033[0m Can't open file."
# define ERR_FILE	"\033[31;1mError :\033[0m File is to large to be handled."
# define ERR_SIZE	"\033[31;1mError :\033[0m Incorrect image dimensions."
# define ERR_SIGN 	"\033[31;1mError :\033[0m Incorrect signature."
# define ERR_COLOR	"\033[31;1mError :\033[0m Incorrect color type."
# define ERR_DEPTH	"\033[31;1mError :\033[0m Incorrect bit depth."
# define ERR_MALLOC "\033[31;1mError :\033[0m Can't allocate memory."
# define ERR_HEADER	"\033[31;1mError :\033[0m Incorrect PNG Header."
# define ERR_PRESET "\033[31;1mError :\033[0m Wrong bit depth - colortype pair."

#endif
