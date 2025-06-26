#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "copy.h"
#include "type_check.h"

int
main(int argc, char** argv) {
  if(argc == 3) {
    int old_file = open(argv[1], O_RDONLY);
    int dest;
    
    char* dest_name = argv[2];
    bool dest_is_dir = is_dir(argv[2]); 

    if(is_dir) {
      strcat(dest_name, "/");
      strcat(dest_name, argv[1]);
      dest = open(dest_name, O_WRONLY | O_CREAT, 0644);
    } else {
      dest = open(argv[2], O_WRONLY | O_CREAT, 0644);
    }

    if(old_file == -1) {
      printf("file not found: %s\n", argv[1]);

      exit(EXIT_SUCCESS);
    }

    copy(old_file, dest);

    close(old_file);
    close(dest);
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
