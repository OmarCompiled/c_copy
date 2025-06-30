#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>

unsigned int
is_dir(const char* dest_name) {
  DIR* dir;
  if((dir = opendir(dest_name)) != NULL) {
		closedir(dir);
    return 1;
	}

  return 0;
}

unsigned int
is_existing_file(const char* file_name) {
  FILE* file;
  if((file = fopen(file_name, O_RDONLY)) != NULL){
		fclose(file);
    return 1;
	}

  return 0;
}

