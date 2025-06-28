#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "copy.h"
#include "type_check.h"

#define MAX_FILE_NAME_SIZE 100

int
main(int argc, char** argv) {
	if(argc >= 3) {
		int old_file;
		int dest;
	
		const char* dest_name = argv[argc-1];

		int i;
		for(i = 1; i < argc - 1; i++) {
			char updated_dest_name[MAX_FILE_NAME_SIZE] = "";
			bool dest_is_dir = is_dir(dest_name);

			old_file = open(argv[i], O_RDONLY);
			 
			if(old_file == -1) {
				printf("file not found: %s\n", argv[i]);

				exit(EXIT_FAILURE);
			}

			if(dest_is_dir) {
				if(dest_name[strlen(dest_name)-1] != '/') { /* This is to prevent undefined behavior */
					strcat(updated_dest_name, dest_name);
					strcat(updated_dest_name, "/");
				}

				strcat(updated_dest_name, argv[i]);
			} 
			
			dest = open(updated_dest_name, O_WRONLY | O_CREAT, 0644);

			copy(old_file, dest);
			printf("copied %s to %s\n",argv[i], updated_dest_name);

			close(old_file);
			close(dest);
		}
	} else if(argc == 2 && !strcmp(argv[1], "-help")) {
		printf("copy [SOURCE] [DEST]\n\n"
				"to display this msg:\n"
				"copy -help\n");

		exit(EXIT_SUCCESS);
	} else {
		printf("invalid command usage.\n"
 				"use -help to see correct usage\n");

		exit(EXIT_FAILURE);
	}

	return 0;
}
