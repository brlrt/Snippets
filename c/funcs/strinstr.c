/**
 * Return pointer to string in string.
 *
 * @param haystack Where to find.
 * @param needle What to find.
 * @return Pointer to first occurrence of needle in haystack or NULL if not
 * found.
 */
char *strinstr(const char *haystack, const char *needle) {
	int len = strlen(needle);
	char *s;

	while (1) {
		if ((s = strchr(haystack, *needle)) == NULL) {
			break;
		}

		if (strncmp(s, needle, len) == 0) {
			return s;
		}

		haystack++;
	}

	return NULL;
}
