#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
	void *handle;
	int (*square)(int);
	const char *error;

	if ((handle = dlopen("./shared.so", RTLD_LAZY)) == NULL) {
		fputs(dlerror(), stderr);
		exit(1);
	}

	square = dlsym(handle, "square");
	if ((error = dlerror()) != NULL)  {
		fputs(error, stderr);
		exit(1);
	}

	printf ("%d\n", (*square)(1));
	printf ("%d\n", (*square)(2));
	printf ("%d\n", (*square)(3));
	dlclose(handle);
	exit(0);
}
