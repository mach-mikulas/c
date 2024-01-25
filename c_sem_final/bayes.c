#include "bayes.h"

/*Vstupní paramery jsou kontrolované ve funkci bayes */
void count(hashtable* ht){

    size_t i;
    item* next_item;

    /* Smyčka běží dokud neprojde přes všechny indexy v tabulce */
    for (i = 0; i < ht->size; ++i) {

        next_item = ht->items[i];

        /* Smyčka běží dokud nedojde na konec řetězového seznamu */
        while(next_item != NULL){
            ht->all_count_spam += next_item->count_spam;
            ht->all_count_ham += next_item->count_ham;

            next_item = next_item->next;
        }

    }

}

/*Vstupní paramery jsou kontrolované ve funkci bayes */
void probabilities(hashtable* ht){
    size_t i;
    item* next_item;

    count(ht);

    /* Smyčka běží dokud neprojde přes všechny indexy v tabulce */
    for (i = 0; i < ht->size; ++i) {

        next_item = ht->items[i];

        /* Smyčka běží dokud nedojde na konec řetězového seznamu */
        while(next_item != NULL){
            next_item->prob_spam = ((double)next_item->count_spam / (double)ht->all_count_spam);
            next_item->prob_ham = ((double)next_item->count_ham / (double)ht->all_count_ham);

            next_item = next_item->next;
        }

    }

}

double prior_prob_spam(hashtable* ht){

    double result;

    result = (double)ht->all_count_spam / (double)(ht->all_count_spam + ht->all_count_ham);

    return result;
}

double prior_prob_ham(hashtable* ht){
    double result;

    result = (double)ht->all_count_ham / (double)(ht->all_count_spam + ht->all_count_ham);

    return result;
}

int bayes_one_file(hashtable* ht, char* test_file_full_name, FILE* output_file){

    FILE* file_test;
    char* word;
    item* tested_item;
    double spam_final_prob = 0;
    double ham_final_prob = 0;
    file_test = file_open_read(test_file_full_name);

    if(file_test == NULL){

        printf("[output] nepodarilo se otevrit testovaci soubor");
        return 1;
    }

    /* Smyčka běží dokud pointer nenarazí na konec programu */
    while(!feof(file_test)){
        word = read_word(file_test);

        if(word == NULL){
            return 1;
        }

        tested_item = hashtable_find(ht, word);

        /* Když se prvek s totožným klíčem vyskytuje v tabulce, přidá se do výpočtu pravděpodobnosti */
        if(tested_item != NULL){

            spam_final_prob += log(tested_item->prob_spam);
            ham_final_prob += log(tested_item->prob_ham);
        }

        free(word);

    }

    fclose(file_test);

    /* Druhá část výpisu výsledku testování (první čast se vypisuje před voláním této funkce) */
    if(spam_final_prob > ham_final_prob){

        fprintf(output_file, "\tS\n");
        /*printf("\tS\n");*/
    }
    else{

        fprintf(output_file, "\tH\n");
        /*printf("\tH\n");*/
    }

    return 0;

}

int bayes(hashtable* ht, char* test_file_name, int test_file_count, char* output_file){

    int i;
    int check;
    FILE* file_output;
    char* test_file_full_name = (char*)malloc(sizeof(char) * STRING_SIZE);

    /* Kontrola vstupních parametrů */
    if((ht == NULL) || (test_file_name == NULL) || (output_file == NULL) || test_file_count < 1){

        printf("[output] wrong parametrs\n");
        printf("spamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n");
        return 1;
    }

    probabilities(ht);

    file_output = fopen(output_file, "w");

    if(file_output == NULL){

        printf("[output] nepodarilo se otevrit vystupni soubor\n");
        return 1;
    }

    /* Smyčka běží dokud nejsou otestovány všechny soubory */
    for (i = 1; i < test_file_count + 1; ++i) {

        /* Složení řetězce cesty k testovacímu souboru */
        sprintf(test_file_full_name,DATA_PATH, test_file_name, i, FILE_FORMAT);

        /* První část výpisu výsledku testování (druhá část se vypisuje ve funkce bayes_one_file()) */
        fprintf(file_output,"%s%d%s", test_file_name, i, FILE_FORMAT);
        /*printf("%s%d%s", test_file_name, i, FILE_FORMAT);*/
        check = bayes_one_file(ht,test_file_full_name, file_output);

        /* Když dojde k chybě, tak je funkce přerušena */
        if(check != 0){
            return 1;
        }
    }

    free(test_file_full_name);
    fclose(file_output);

    return 0;

}