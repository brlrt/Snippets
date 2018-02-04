#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	FILE *fh = fopen(argv[1], "rb");
	if (fh == NULL) {
		perror("fopen");
		exit(1);
	}

	setlocale(LC_CTYPE, "");
	wint_t c;
	while ((c = fgetwc(fh)) != WEOF) {
		wprintf(L"%lc\n", c);
	}
	fclose(fh);

	exit(0);
}
