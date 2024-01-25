#include "hashtable.h"

/* Vstupní parametry testovány ve funkci ve které je tato funkce volána*/
size_t hash(hashtable* ht, const char* key){

    int j;
    int i = 0;
    for (j = 0; key[j]; ++j)
        i += key[j];
    return i % ht->size;
}

/* Vstupní parametry testovány ve funkci ve které je tato funkce volána*/
item* item_create(char* key, int spam_or_ham){

    item* new_item;

    if(strlen(key) == 0){
        return NULL;
    }

    new_item = (item*)malloc(sizeof(item));

    if(!new_item){
        return NULL;
    }

    new_item->key = (char*)malloc(strlen(key) + 1);

    if (!new_item->key){
        free(new_item);
        return NULL;
    }

    strcpy(new_item->key, key);

    new_item->count_ham = 1;
    new_item->count_spam = 1;
    new_item->next = NULL;

    add_cont(new_item,spam_or_ham);

    return new_item;

}

hashtable* hashtable_create(size_t size){

    size_t i;
    hashtable* new_hashtable;

    if(size == 0){
        return NULL;
    }

    new_hashtable = (hashtable*) malloc(sizeof(hashtable));

    if(new_hashtable == NULL){
        return NULL;
    }

    new_hashtable->all_count_ham = 0;
    new_hashtable->all_count_spam = 0;
    new_hashtable->size = size;
    new_hashtable->items = (item**) calloc(size, sizeof(item*));

    if(new_hashtable->items == NULL){

        free(new_hashtable);
        return NULL;
    }

    for (i = 0; i < size; i++)
        new_hashtable->items[i] = NULL;

    return new_hashtable;
}

item* hashtable_find(hashtable* table, char* key){

    size_t pozice;
    int result;
    item* item;

    /* Kontrola vstupních parametrů */
    if((table == NULL) && (key == NULL)){
        return NULL;
    }

    pozice = hash(table, key);

    /* Pokud hledaný prvek v tabulce není, tak vrátí NULL */
    if(table->items[pozice] == NULL){
        return NULL;
    }

    item = table->items[pozice];
    result = strcmp(table->items[pozice]->key, key);

    /* Smyčka běží dokud nenajde hledaný prvek nebo nenarazí na konec spojového seznamu */
    while(result != 0){

        item = item->next;

        /* Pokud hledaný prvek v tabulce není, tak vrátí NULL */
        if(item == NULL){
            return NULL;
        }

        result = strcmp(item->key, key);

    }

    return item;

}

int hashtable_insert(hashtable* table, char* key, int spam_or_ham){

    size_t pozice;
    item* new_item;
    item* volna_pozice;

    /* Kontrola vstupních parametrů */
    if((table == NULL) && (key == NULL)){
        printf("Spatny vstup\n");
        return -1;
    }

    /* Pokud prvek s totožným klíčem už je v tabulce */
    if((new_item = hashtable_find(table, key)) != NULL){

        add_cont(new_item, spam_or_ham);

        return 1;
    }


    pozice = hash(table, key);
    new_item = item_create(key, spam_or_ham);

    volna_pozice = table->items[pozice];

    if(table->items[pozice] == NULL){
        table->items[pozice] = new_item;
        return 1;
    }

    while (volna_pozice->next != NULL){
        volna_pozice = volna_pozice->next;
    }

    volna_pozice->next = new_item;

    return 1;
}

void item_free(item** it){

    if ((it == NULL) || ((*it) == NULL)) {
        return;
    }

    if((*it)->key != NULL){
        free((*it)->key);
    }

    /* Rekurzivně uvolní všechny zřetězené prvky */
    item_free(&(*it)->next);

    free(*it);
    *it = NULL;

}

void hashtable_free(hashtable** table){


    size_t i;

    if ((table == NULL) || ((*table) == NULL)) {
        return;
    }

    for (i = 0; i < (*table)->size; ++i) {
        item_free(&(*table)->items[i]);
    }

    free((*table)->items);
    free(*table);
    *table = NULL;

}

/*
void hastable_print(hashtable* table){

    size_t i;
    item* next;

    for (i = 0; i < table->size; i++){

        printf("%llu: ", i);

        if(table->items[i] != NULL){
            next = table->items[i];
            while(next != NULL){
                printf("%s|prob_spam: %f|prob_ham: %f, ", next->key, next->prob_spam, next->prob_ham);
                next = next->next;
            }
        }

        printf("\n");

    }
}
*/

void add_cont(item* it, int spam_or_ham){

    if(it == NULL){
        return;
    }

    if(spam_or_ham == 0){
        it->count_spam +=1;
    }
    else{
        it->count_ham +=1;
    }
}

