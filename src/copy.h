#ifndef COPY_H
#define COPY_H

#define BUFFER_SIZE 4096 /*4 Kib*/

int
copy(int old_fd, int dest) {
  /* I understand 4096 bytes isn't always enough,
     this is just an arbitrary number. I'll try
     to fix it later.
   */
  char buffer[BUFFER_SIZE];
  int  bytes_read = read(old_fd, buffer, sizeof(buffer));

  write(dest, buffer, bytes_read);
  
  return bytes_read;
}

/*void
multi_copy(int old_fds[], int dest) {
  int old_fds_length = sizeof(old_fds) / sizeof(old_fds[0]);

  int i;
  for(i = 0; i < old_fds_length; i++) {
    copy(old_fds[i], dest);
  }
}*/

#endif
