/**
 * @file bayes.h
 * @author Mikuláš Mach
 * @brief Hlavičkový soubor s deklaracemi funkcí pro klasifikaci testovaných souborů.
 * @version 1.0
 * @date 2022-12-27
 */
#ifndef BAYES_H
#define BAYES_H

#include "input.h"
#include "hashtable.h"
#include <math.h>
#include <stdio.h>

/**
 * @brief Funkce pro aktualizaci počtu spamu a hamu v tabulce.
 * @param ht Ukazatel na tabulku.
 * @return 0 pokud vše proběhlo v pořádku.
 */
void count(hashtable* ht);

/**
 * @brief Funkce pro aktualizaci pravděpodobností výskytu slov ve spamu a v hamu.
 * @param ht Ukazatel na tabulku.
 * @return 0 pokud vše proběhlo v pořádku.
 */
void probabilities(hashtable* ht);

double prior_prob_spam(hashtable* ht);

double prior_prob_ham(hashtable* ht);

/**
 * @brief Funkce, která vyhodnotí zda testovací soubor je HAM nebo SPAM a výsledek zapíše do výstupního souboru.
 * @param ht Ukazatel na tabulku.
 * @param test_file_full_name Cesta k testovacímu souboru.
 * @param output_file Ukazatel na výstupní soubor.
 * @return 0 pokud vše proběhlo v pořádku.
 */
int bayes_one_file(hashtable* ht, char* test_file_full_name, FILE* output_file);

/**
 * @brief Funkce, která rozhodne o všech testovaných souborech zda jsou spam nebo ham a výsledek zapíše do výstupního souboru
 * @param ht Ukazatel na tabulku.
 * @param test_file_full Vzor názvu testovaných souborů.
 * @param test_file_count Počet testovaných souborů.
 * @param output_file Celý název výstupního souboru.
 * @return 0 pokud vše proběhlo v pořádku.
 */
int bayes(hashtable* ht, char* test_file_name, int test_file_count, char* output_file);


#endif
