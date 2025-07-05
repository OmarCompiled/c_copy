#include <stdio.h>
#include <stdlib.h>

#include "copy.h"
#include "utils.h"

int
main(int argc, char** argv) {
	if(argc == 3 && !is_dir(argv[1]))
		if(copy(argv[1], argv[argc-1]) < 0) {
			exit(EXIT_FAILURE);
		}	

	return 0;
}
