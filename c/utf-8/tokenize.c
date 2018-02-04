#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*
	Beware - do not mix output on printf and wprintf - they are
	different streams
*/
int main(int argc, char *argv[])
{
	wchar_t *string = L"æøåÆØÅ";
	int i, len;

	setlocale(LC_CTYPE, "");
	len = wcslen(string);
	for (i = 0; i < len; i++) {
		wchar_t c = string[i];
		wprintf(L"%lc\n", c);
	}

	return 0;
}

