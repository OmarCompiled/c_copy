#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>

bool
is_dir(const char* dest_name) {
  DIR* dir;
  if((dir = opendir(dest_name)) != NULL) {
		closedir(dir);
    return true;
	}

  return false;
}

bool
is_existing_file(const char* file_name) {
  FILE* file;
  if((file = fopen(file_name, O_RDONLY)) != NULL){
		fclose(file);
    return true;
	}

  return false;
}

