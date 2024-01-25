/**
 * @file input.h
 * @author Mikuláš Mach
 * @brief Hlavičkový soubor s deklaracemi funkcí pro načítaní souborů.
 * @version 1.0
 * @date 2022-12-26
 */

#ifndef INPUT_H
#define INPUT_H


#include "hashtable.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Funkce otevře soubor pro čtení.
 * @param filename ukazatel na pole znaků uchovávající název souboru.
 * @return Ukazatel na otevřený soubor nebo NULL při chybě.
 */
FILE* file_open_read(char* filename);

/**
 * @brief Funkce pro přečtení jedhono slova ze souboru.
 * @param file Ukazatel na otevřený soubor.
 * @return Ukazatel na načtené slovo nebo NULL při chybě.
 */
char* read_word(FILE* file);

/**
 * @brief Funkce pro přečtení a vložení všech slov ze spam souboru do tabulky.
 * @param ht Ukazatel na tabulku.
 * @param spam_file_name Ukazatel na název souboru.
 * @param spam_file_count Počet načítaných souborů.
 * @return 0 pokud vše proběhlo správně.
 */
int load_spam(hashtable* ht, char* spam_file_name, int spam_file_count);

/**
 * @brief Funkce pro přečtení a vložení všech slov z ham souborů do tabulky.
 * @param ht Ukazatel na tabulku.
 * @param ham_file_name Ukazatel na název souboru.
 * @param ham_file_count Počet načítaných souborů.
 * @return 0 pokud vše proběhlo správně.
 */
int load_ham(hashtable* ht, char* ham_file_name, int ham_file_count);


#endif
