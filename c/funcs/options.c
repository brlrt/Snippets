#include <stdio.h>
#include <string.h>

/* globals */
int optind = 1;
char *optarg = NULL;

/**
 * Get next option (pair) from the argument list.
 *
 * @param argc Arg count.
 * @param argv Arg list.
 * @param optstr Option string.
 * @return option, '?' (unknown option) or ':' (missing argument to option).
 */
int getopt(int argc, char * const *argv, const char *optstr) {
	char *p;

	if ((optind >= argc) || (argv[optind][0] != '-')) {
		return -1;
	}

	if (argv[optind][1] == '-') {
		optind++;
		return -1;
	}

	if ((p = strchr(optstr, argv[optind][1]))) {
		if (p[1] == ':') {
			if (argv[optind][2]) {
				optarg = &argv[optind][2];
			} else {
				optind++;
				if (optind >= argc) {
					return ':';
				}

				optarg = argv[optind];
			}
		}

		optind++;
		return (int)*p;
	}

	return '?';
}
