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

int
copy(const char* src, const char* dest_name) {
	char buffer[BUFFER_SIZE];
	int bytes_read;
	int source;
	int dest;	
	
	if((source = open(src, O_RDONLY)) < 0) {
			printf("error: file not found: %s\n", src);

			return -1;
	}

	if((dest = open(dest_name, O_WRONLY | O_CREAT, 0644)) < 0) {
			printf("error: could not create file: %s\n", dest_name);
		
			return -1;	
	}

	if((bytes_read = read(source, buffer, sizeof(buffer))) < 0) {
			printf("error: could not copy file: %s\n", dest_name);

			return -1;
	}

	if(write(dest, buffer, bytes_read) < 0) {
			printf("error: could not write to file: %s\n", dest_name);

			return -1;
	}
		
	close(source);
	close(dest);
  
	return 0;
}

int
copy_multiple_files(const int argc, char** argv, const char* dest_name) {
	int multiplier = strlen(dest_name) * 4;

	int i;
	for(i = 1; i < argc - 1; i++) {
		char* updated_dest_name = (char*)malloc(sizeof(char) * multiplier);
		
		/* I have to initialize space since malloc 
			 just allocates and doesn't initialize */
		*updated_dest_name = '\0';

		if(is_dir(argv[i]))
				continue;
			 
		strcat(updated_dest_name, dest_name);
		if(dest_name[strlen(dest_name)-1] != '/') { /* This is to prevent undefined behavior */
				strcat(updated_dest_name, "/");
		}

		strcat(updated_dest_name, argv[i]);

		if(copy(argv[i], updated_dest_name) < 0) {
				printf("error: could not copy file: %s\n", argv[i]);

				return -1;	
		}

		free(updated_dest_name);

		return 0;
	}
}
