int		big_endian(char *length)
{
	return (((unsigned char)length[0] << 24)
		| ((unsigned char)length[1] << 16)
		| ((unsigned char)length[2] << 8)
		| ((unsigned char)length[3]));
}

int		is_power_two(int nb)
{
	return ((nb == 1 || nb == 2 || nb == 4 || nb == 8 || nb == 16 ? 1 : 0));
}
