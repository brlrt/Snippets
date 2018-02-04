/**
 * Compare two strings.
 *
 * @param s1 String 1.
 * @param s2 String 2.
 * @return -1, 0, 1 whether s1 is smaller, same or larger than s2.
 */
int strcompare(char *s1, char *s2) {
	while (*s1 == *s2) {
		if ((*s1 == '\x00') || (*s2 == '\x00')) {
			break;
		}

		s1++;
		s2++;
	}

	if (*s1 == '\x00') {
		if (*s2 == '\x00') {
			return 0;
		}

		return -1;
	}

	if (*s2 == '\x00') {
		return 1;
	}

	if (*s1 < *s2) {
		return -1;
	}

	return 1;
}
