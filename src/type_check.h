#ifndef TYPE_CHECK_H
#define TYPE_CHECK_H

#include <dirent.h>

bool
is_dir(const char* dest) {
  DIR* dir;
  if((dir = opendir(dest)) != NULL)
    return true;

  return false;
}

#endif
