#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096 /*4 Kib*/

int
copy(int old_fd, int dest) {
  /* I understand 4096 bytes isn't always enough,
     this is just an arbitrary number. I'll try
     to fix it later.
   */
	char buffer[BUFFER_SIZE];
	int  bytes_read = read(old_fd, buffer, sizeof(buffer));

	write(dest, buffer, bytes_read);
  
	return bytes_read;
}

