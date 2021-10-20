#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "42-libft/libft.h"

int main(void)
{
	char const *filename = "pokeemerald.sym";
	char const *newfile = "parsed.txt";
	FILE *sym;
	FILE *txt;
	char	*buffer;
	char **sym_array;
	char **line;
	long lSize;
	int	i;

	i = 0;
	//stolen from stack overflow
	sym = fopen(filename, "rb");
	txt = fopen(newfile, "w");
	fseek( sym , 0L , SEEK_END);
	lSize = ftell(sym);
	rewind(sym);

	if (txt == NULL)
		return (1);
	buffer = calloc( 1, lSize+1 );
	if( !buffer ) fclose(sym),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	if( 1!=fread( buffer , lSize, 1 , sym) )
  		fclose(sym),free(buffer),fputs("entire read fails",stderr),exit(1);

	//printf("%s\n", buffer);
	//Split string into multiple substrings. Long time to process, cant make it quicker im already using syscalls
	sym_array = ft_split(buffer, '\n');
	free(buffer); //dont need it anymore
	while (sym_array[i])
	{
		if (ft_strnstr(sym_array[i], "MapWarps", ft_strlen(sym_array[i])) != NULL) //only if the array contains MapWarps, we take the address and output to a txt file
		{
			printf("%s\n", sym_array[i]);
			line = ft_split(sym_array[i], ' ');
			fputs(line[0], txt);
			fputs("\n", txt);
		}
		i++;
	}
	i = 0;
	//free all the mem
	while (sym_array[i])
		free(sym_array[i]);
	fclose(sym);
	fclose(txt);
	return (0);
}