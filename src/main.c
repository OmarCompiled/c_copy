#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "copy.h"
#include "type_check.h"


int
main(int argc, char** argv) {
	const char* dest_name = argv[argc-1];

	if(argc >= 3 && is_dir(dest_name)) {
		copy_multiple_files(argc, argv, dest_name);
	} else if(argc == 3) {
		copy(argv[1], dest_name);
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
