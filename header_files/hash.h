
/*API FOR HASH TABLE*/

typedef struct item
{
	char *key;
	char *value 
}item_ty;

typedef int (*Hash_Func)(int *id);

typedef struct hash_table
{
	Hash_Func hash_function;
	
	item_ty** items;
	
	int size;
}ht_ty;

ht_ty *HTCreate(int size, Hash_Func hash_function);

void HTDestory(ht_ty *table);

int HTInsert(ht_ty *table, char *key, char *value);

void HTRemove(ht_ty *table, char *key)

char *HTFind(ht_ty *table, char* key);






