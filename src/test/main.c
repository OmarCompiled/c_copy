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

RDONLY);

			 if(dest_is_dir) {
				if(dest_name[strlen(dest_name)-1] != '/') /* This is to prevent undefined behavior */
					strcat(dest_name, "/");

				strcat(dest_name, argv[i]);
				dest = open(dest_name, O_WRONLY | O_CREAT, 0644);
			} else {
				dest = open(dest_name, O_WRONLY | O_CREAT, 0644);
			}

			if(old_file == -1) {
				printf("file not found: %s\n", argv[i]);

				exit(EXIT_FAILURE);
			}

			copy(old_file, dest);

			close(old_file);
			close(dest);
		}
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
