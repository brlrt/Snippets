typedef void *HashTable;

HashTable hash_new(int);
void hash_free(HashTable, int);
#define HT_PRESERVE_VALUE 0
#define HT_FREE_VALUE 1
int hash_add(HashTable, const char *, const void *, int, int);
void *hash_get(HashTable, const char *, int *);
int hash_delete(HashTable, const char *);
int hash_find_first(HashTable, const char **, const void **, int *);
int hash_find_next(HashTable, const char **, const void **, int *);
