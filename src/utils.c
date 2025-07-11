#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int
is_dir(const char* path) {
	struct stat path_stat;
	stat(path, &path_stat);

	return S_ISDIR(path_stat.st_mode);
}

int
is_existing_file(const char* path) {
	struct stat path_stat;
	stat(path, &path_stat);

	return S_ISREG(path_stat.st_mode);
}
