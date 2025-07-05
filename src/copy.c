#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

/* This function only copies file contents. my intention is to 
  write another function that handles file paths : copy */
int
copy_content(const char* src_path, const char* dest_path) {
	int source, destination, bytes_read;
	char buffer;

	if((source = open(src_path, O_RDONLY)) < 0) {
		fprintf(stderr, "error opening file %s: %s\n", src_path, strerror(errno));

		return -1;
	}

	if((destination = open(dest_path, O_WRONLY | O_CREAT, 0644)) < 0) {
		perror("open");

		return -1;
	}

	while((bytes_read = read(source, &buffer, 1)) && bytes_read != 0) {
		if(bytes_read < 0) {
			perror("read");

			return -1;
		}

		if(write(destination, &buffer, 1) < 0) {
			perror("write");

			return -1;
		}
	}

	return 0;
}

/* This function should handle the paths, and 
 internally use copy_content after correcting paths */
int
copy(const char* old_src_path, const char* old_dest_path) {
	char* new_dest_path = (char*)malloc(sizeof(char) * strlen(old_dest_path) * 10);
	*new_dest_path = '\0';

	if(is_dir(old_dest_path)) {
		strcat(new_dest_path, old_dest_path);
		if(old_dest_path[strlen(old_dest_path)-1] != '/') {
			strcat(new_dest_path, "/");
		}

		strcat(new_dest_path, old_src_path);

		if(copy_content(old_src_path, new_dest_path) < 0) {
			return -1;
		}
	}

	return 0;
}
