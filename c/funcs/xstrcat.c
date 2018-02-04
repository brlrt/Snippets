/**
 * Concatenate up to gazillion strings.
 *
 * @param sep Separator (or NULL if no separator).
 * @param ... Strings to concatenate.
 * @return '\0' terminated string or NULL (error).
 * @note The list of strings must be NULL terminated.
 */
char *xstrcat(char *sep, ...) {
	int str_len = 0, entries = 0, sep_len, len;
	char *dst, *s, *w;
	va_list l;

	if (sep == NULL) {
		sep_len = 0;
	} else {
		sep_len = strlen(sep);
	}

	/* find length of entries & no. of entries */
	va_start(l, sep);
	while ((s = va_arg(l, char *)) != NULL) {
		str_len += strlen(s);
		entries++;
	}
	va_end(l);

	/* allocate string */
	if ((entries--) < 0) {
		return NULL;
	}

	str_len += (entries * sep_len) + 1;
	if ((dst = calloc(str_len, 1)) == NULL) {
		return NULL;
	}

	/* create string */
	w = dst;
	va_start(l, sep);
	while ((s = va_arg(l, char *)) != NULL) {
		len = strlen(s);
		strncpy(w, s, len);
		w += len;
		entries--;
		if (entries < 0) {
			break;
		}

		if (sep_len > 0) {
			strncpy(w, sep, sep_len);
			w += sep_len;
		}
	}
	va_end(l);

	/* terminate string */
	*w = '\x00';
	return dst;
}
