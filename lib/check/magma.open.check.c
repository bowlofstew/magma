
#include "magma.open.check.h"

void symbols_check(void *);

int main(int argc, char **argv) {

	void *handle;
	char libpath[1024], *basepath, *copypath = NULL;

	if (argc >= 2)
			snprintf(libpath, 1024, "%s", argv[1]);
	else
		snprintf(libpath, 1024, "%s", "magmad.so");

	if (!(handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL))) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	if ((copypath = strdup(libpath)) && (basepath = basename(libpath))) {
		printf("%s loaded...\n\n", basepath);
	}
	else {
		printf("%s loaded...\n\n", libpath);
	}

	if (copypath) free(copypath);

	// Check and see if any of our symbols trigger an error.
	symbols_check(handle);

	if (dlclose(handle)) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
