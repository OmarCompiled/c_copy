#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "type_check.h"

/* I understand 4096 bytes isn't always enough,
     this is just an arbitrary number. I'll try
     to fix it later.
*/
#define BUFFER_SIZE 4096 /*4 Kib*/
#define MAX_FILE_NAME_SIZE 100

int
copy(const char* src, const char* dest_name) {
	char buffer[BUFFER_SIZE];
	int source;
	int dest;

	source = open(src, O_RDONLY);
	dest = open(dest_name, O_WRONLY | O_CREAT, 0644);
	
	if(source == -1) {
		printf("file not found: %s\n", src);

		exit(EXIT_FAILURE);
	}

	int  bytes_read = read(source, buffer, sizeof(buffer));

	write(dest, buffer, bytes_read);
		
	close(source);
	close(dest);
  
	return bytes_read;
}

void
copy_multiple_files(const int argc, char** argv, const char* dest_name) {
	int i;
	for(i = 1; i < argc - 1; i++) {
		char updated_dest_name[MAX_FILE_NAME_SIZE] = ""; /* sizing is necessary here, otherwise it'll be immutable & 1 byte */
			
		if(is_dir(argv[i]))
			continue;
			 
		
		strcat(updated_dest_name, dest_name);
		if(dest_name[strlen(dest_name)-1] != '/') { /* This is to prevent undefined behavior */
			strcat(updated_dest_name, "/");
		}

		strcat(updated_dest_name, argv[i]);

		copy(argv[i], updated_dest_name);
	}
}
