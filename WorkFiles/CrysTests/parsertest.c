/*
**	Test function for the various elements of parser.c
*/

#include "../../ProjectFiles/fillitproject/includes/fillit.h"
#include <stdio.h>

t_piece *printpiecelist(t_piece *piecelist);
void	printpiece(t_piece *piece);

t_piece		*makepiece(char* buf, char pieceletter)
{
	t_piece	*piece_ptr;
	int	x;
	int y;
	int i;

	i = 0;
	x = 0;
	y = 1;
	if (!(piece_ptr = (t_piece*)malloc(sizeof(t_piece))))
		return (NULL);
	while(i < 20)
	{
		if(buf[i] == '#')
		{
			piece_ptr->blockcoords[x] = (i > 5) ? (i % 5) : i;
			piece_ptr->blockcoords[y] = i / 5;
			x += 2;
			y += 2;
		}
		i++;
	}
	piece_ptr->pieceletter = pieceletter;
	//align(piece_ptr);
	return (piece_ptr);
}

t_piece		*makelist(char *buf) // too many lines -- may be best to edit validity checker to work on entire file instead of chunks, to be called in parser -- would save 5 lines
{
	t_piece *current;
	t_piece *beginning;
	int 	i;
	char	pieceletter;

	i = 0;
	pieceletter = 'A';
	while (buf[i])
	{
		if (pieceletter == 'A')
		{
			beginning = makepiece(buf + i, pieceletter);
			current = beginning;
		}
		else
		{
			current->next = makepiece(buf + i, pieceletter);
			current = current->next;
		}
		pieceletter++;
		i = i+21;
	}
	return (beginning);
}

t_piece		*parser(char *filename)
{
	char	buf[545];
	int		fd;
	int		bytecount;

	fd = open(filename, O_RDONLY);
	bytecount = read(fd, buf, 545);
	if (bytecount > 544 || bytecount < 20)
		return (NULL);
	buf[bytecount] = '\0';
//	if(!valid(buf))		// re-work validitychecker to work with whole file instead of 21-char chunk
//		return(NULL);
	return (makelist(buf));
}

int	main(void)
{
	t_piece *listhead = parser("../TestFiles/26Pieces");
	printpiecelist(listhead);
	return (0);	
}
