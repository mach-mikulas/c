#include "input.h"
#include "bayes.h"

int main(int argc, char *argv[]) {

    int check;
    char* spam_file_name;
    int spam_file_count;
    char* ham_file_name;
    int ham_file_count;
    char* test_file_name;
    int test_file_count;
    char* output_file;
    hashtable* ht;

    if(argc < 8){
        printf("Wrong number of arguments. Try again\n");
        printf("spamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n");
        return 1;
    }

    ht = hashtable_create(HASHTABLE_SIZE);

    if(ht == NULL){
        return 1;
    }

    /* Některé hodnoty jsou kontrolované až ve volaných funkcích */
    spam_file_name = argv[1];
    spam_file_count = strtol(argv[2], NULL, 0);
    ham_file_name = argv[3];
    ham_file_count = strtol(argv[4], NULL, 0);
    test_file_name = argv[5];
    test_file_count = strtol(argv[6], NULL, 0);
    output_file = argv[7];

    /* Načtení spam souborů */
    check = load_spam(ht, spam_file_name, spam_file_count);

    if(check != 0){
        hashtable_free(&ht);
        return 1;
    }

    /* Načtení ham souborů */
    check = load_ham(ht, ham_file_name, ham_file_count);

    if(check != 0){
        hashtable_free(&ht);
        return 1;
    }

    /* Vyhodnocení testovacích souborů */
    bayes(ht, test_file_name, test_file_count, output_file);

    hashtable_free(&ht);

    return 0;
}
