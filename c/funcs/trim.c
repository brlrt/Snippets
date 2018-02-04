/**
 * Trim (remove blank charaters in front of and at the end of) the input string.
 *
 * @param src Source string.
 * @return Trimmed string.
 * @note Trimming will be done in-place.
 */
char *trim(char *src) {
	int len = strlen(src);

	if (len) {
		int idx, end;

		while (len && isspace((int) src[len - 1])) {
			len--;
		}

		for (idx = 0; (idx < len) && (isspace((int) src[idx])); idx++) ;

		end = len - idx;

		if (end) {
			memmove(src, src + idx, end);
		}

		src[end] = 0;
	}

	return src;
}
