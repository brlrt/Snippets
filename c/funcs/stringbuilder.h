
/* stringbuilder.c */
typedef void * StringBuilder;

StringBuilder stringbuilder_new(int g);
void stringbuilder_free(StringBuilder s);
void stringbuilder_append(StringBuilder s, char *src, int len);
void stringbuilder_append_char(StringBuilder s, char src);
char *stringbuilder_to_string(StringBuilder s);
int stringbuilder_length(StringBuilder s);
void stringbuilder_set_length(StringBuilder s, int len);
void stringbuilder_reset(StringBuilder s);
void stringbuilder_copy_to(StringBuilder src, StringBuilder dst);
int stringbuilder_position(StringBuilder s);
