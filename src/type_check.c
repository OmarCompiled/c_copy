#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>

short int is_dir(const char *dest_name) {
  DIR *dir;
  if ((dir = opendir(dest_name)) != NULL) {
    closedir(dir);
    return 1;
  }

  return 0;
}
