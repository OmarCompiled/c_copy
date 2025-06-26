#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int
copy(int old_fd, int new_fd) {
  /* I understand 1024 bytes isn't always enough,
     this is just an arbitrary number. I'll try
     to fix it later.
   */
  char buffer[BUFFER_SIZE];
  int  bytes_read = read(old_fd, buffer, sizeof(buffer));

  write(new_fd, buffer, bytes_read);
  
  return bytes_read;
}

int
main(int argc, char** argv) {
  if(argc == 3) {
    int old_file = open(argv[1], O_RDONLY);
    int new_file;
    
    char* new_file_name = argv[2];
    if(argv[2][strlen(argv[2])-1] == '/') {
      strcat(new_file_name, argv[1]);
      new_file = open(new_file_name, O_WRONLY | O_CREAT, 0644);
    } else {
      new_file = open(argv[2], O_WRONLY | O_CREAT, 0644);
    }

    if(old_file == -1) {
      printf("file not found: %s\n", argv[1]);

      exit(EXIT_SUCCESS);
    }

    copy(old_file, new_file);

    close(old_file);
    close(new_file);
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
