#include <unistd.h> 
#include <fcntl.h>	
#include <stdio.h>	

int main(void)
{
	int 			fd;
	unsigned char 	c;
	ssize_t 		bytes_read;
	unsigned char 	buffer[6000];
	unsigned char 	new_char;

	fd = open("token", O_RDONLY);
	if (fd == -1)
	{
		printf("open fail. make sure token file exists");
		return (1);
	}

	int i = 0;
	while ((bytes_read = read(fd, &c, 1)) > 0)
	{
		if(c == '\n')
			break ; 
			
		new_char = c - i;

		printf("[%d]		=	%02x	=> %c\n", i + 1, new_char, new_char);
		buffer[i] = new_char;
		i++;
	}
	buffer[i] = 0;

	printf("\n[END] - final string is: %s", buffer);
	

	if (bytes_read == -1)
		printf("read fail");

	close(fd);
	return 0;
}
