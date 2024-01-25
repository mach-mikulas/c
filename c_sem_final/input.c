#include "input.h"

/* Vstupní argument je kontrolován v nadřazené funkci */
FILE* file_open_read(char* filename){

    FILE* file;
    file = fopen(filename, "r");

    if(file == NULL){
        return NULL;
    }

    return file;

}

char* read_word(FILE* file){

    char* buffer = (char*)malloc(sizeof(char) * STRING_SIZE);
    char* string;
    char c;
    int i = 0;
    int j;
    int string_size = 0;

    /* Smyčka postupně načítá charaktery dokud nenarazí na mezeru nebo na konec souboru */
    while((c = fgetc(file)) != ' ' && !feof(file)){
        buffer[i] = c;
        i++;
        string_size++;
    }

    string = (char*)malloc(sizeof(char) * string_size + 1);

    if(string == NULL){
        free(buffer);
        return NULL;
    }

    /* Kopírování načteného řetězce z bufferu do pole o ideální velikosti */
    for (j = 0; j < string_size; ++j) {
        string[j] = buffer[j];
    }

    /* Přidání nulového znaku na konec řetězce */
    string[string_size] = '\0';

    free(buffer);

    return string;
}

int load_spam(hashtable* ht, char* spam_file_name, int spam_file_count){

    int i;
    FILE* file;
    char* word;
    char* full_file_name = (char*)malloc(sizeof(char) * STRING_SIZE);

    /* Kontrola vstupních parametrů */
    if((ht == NULL) || (spam_file_name == NULL) || spam_file_count < 1){
        printf("[load_spam] wrong parametrs\n");
        printf("spamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n");
        free(full_file_name);
        return 1;
    }

    /* Smyčka běží, dokud nejsou načteny všechny souboru typu spam */
    for (i = 1; i < spam_file_count + 1; ++i) {

        sprintf(full_file_name, DATA_PATH, spam_file_name, i, FILE_FORMAT);

        file = file_open_read(full_file_name);

        if(file == NULL){
            printf("[load_spam] soubor: %s se nepodarilo otevrit\n" , full_file_name);
            free(full_file_name);
            return 1;
        }

        /* Smyčka beží, dokud pointer nenarazí na konec souboru */
        while(!feof(file)){
            word = read_word(file);
            hashtable_insert(ht, word, 0);
            free(word);

        }

        fclose(file);

    }

    free(full_file_name);
    full_file_name = NULL;

    return 0;
}

int load_ham(hashtable* ht, char* ham_file_name, int ham_file_count){

    int i;
    FILE* file;
    char* word;
    char* full_file_name = (char*)malloc(sizeof(char) * STRING_SIZE);

     /* Kontrola vstupních parametrů */
    if((ht == NULL) || (ham_file_name == NULL) || ham_file_count < 1){
        printf("[load_ham] wrong parametrs\n");
        printf("spamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n");
        free(full_file_name);
        return 1;
    }

    /* Smyčka běží, dokud nejsou načteny všechny souboru typu ham */
    for (i = 1; i < ham_file_count + 1; ++i) {

        sprintf(full_file_name, DATA_PATH, ham_file_name, i, FILE_FORMAT);

        file = file_open_read(full_file_name);

        if(file == NULL){
            printf("[load_ham] soubor: %s se nepodarilo otevrit\n" , full_file_name);
            free(full_file_name);
            return 1;
        }

        /* Smyčka beží, dokud pointer nenarazí na konec souboru */
        while(!feof(file)){
            word = read_word(file);
            hashtable_insert(ht, word, 1);
            free(word);
        }

        fclose(file);

    }

    free(full_file_name);
    full_file_name = NULL;

    return 0;
}