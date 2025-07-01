#include <errno.h>
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

	/* Since most -if not all- return -1 on failure, 
	   that's what I'll test for. Perhaps I'll change this to errno later on.*/	
	if((source = open(src, O_RDONLY)) < 0) {
			fprintf(stderr, "error copying file %s: %s\n", src, strerror(errno));

			return -1;
	}

	if((dest = open(dest_name, O_WRONLY | O_CREAT, 0644)) < 0) {
			perror(NULL);
		
			return -1;	
	}

	if((bytes_read = read(source, buffer, sizeof(buffer))) < 0) {
			fprintf(stderr, "error reading file %s: %s\n", src, strerror(errno));

			return -1;
	}

	if(write(dest, buffer, bytes_read) < 0) {
			perror(NULL);	

			return -1;
	}
		
	if(close(source) < 0 || close(dest) < 0) {
			/* Not sure what to print */
			perror(NULL);
			return -1;
	}
  
	return 0;
}

int
copy_multiple_files(const int argc, char** argv, const char* dest_name) {
	int multiplier = strlen(dest_name) * 100;

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
				/* error messages from copy() are enough, just returning */
				return -1;	
		}

		free(updated_dest_name);
	}

	return 0;
}
