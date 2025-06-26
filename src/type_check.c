#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>

bool
is_dir(const char* dest_name) {
  DIR* dir;
  if((dir = opendir(dest_name)) != NULL)
    return true;

  return false;
}

bool
is_existing_file(const char* file_name) {
  FILE* file;
  if((file = fopen(file_name, O_RDONLY)) != NULL)
    return true;

  return false;
}

