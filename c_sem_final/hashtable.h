/**
 * @file hashtable.h
 * @author Mikuláš Mach
 * @brief Hlavičkový soubor s deklaracemi funkcí pracujících s tabulkovou strukturou.
 * @version 2.0
 * @date 2022-12-23
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Definice struktury jednoho prvku tabulky.
 */
typedef struct hashtable_item_ {

    /** Klíč prvku*/
    char* key;
    /** Počet, určující kolikrát byl tento prvek vkládán jako ham*/
    size_t count_ham;
    /** Počet, určující kolikrát byl tento prvek vkládán jako spam*/
    size_t count_spam;
    /** Pravděpodobnost že výskytu z množiny ham*/
    double prob_ham;
    /** Pravděpodobnost že výskytu z množiny spam*/
    double prob_spam;

    struct hashtable_item_* next;

} item;

/**
 * @brief Definice tabulkové struktury.
 */
typedef struct hashtable_ {

    /** Počet, určující kolikrát byl ham vkládán do tabulky*/
    size_t all_count_ham;
    /** Počet, určující kolikrát byl spam vkládán do tabulky*/
    size_t all_count_spam;
    /** Velikost tabulky*/
    size_t size;
    /** Ukazatel na pole prvků*/
    item** items;

} hashtable;

/**
 * @brief Funkce pro převedení klíče na hash.
 * @param key Ukazatel na klíč.
 * @return Vrací hash.
 */
size_t hash(hashtable* ht, const char* key);

/**
 * @brief Funkce pro vytvoření nového prvku tabulky.
 * @param key Ukazatel na klíč.
 * @return item* Ukazatel na nově vytvořenou položku nebo NULL při chybě.
 */
item* item_create(char* key, int spam_or_ham);

/**
 * @brief Funkce pro vytvoření nové tabulky.
 * @param size Velikost tabulky.
 * @return hashtable* Ukazatel na nově dynamicky alokovanou tabulku nebo NULL při chybě.
 */
hashtable* hashtable_create(size_t size);

/**
 * @brief Funkce pro vložení prvku do tabulky.
 * @param table Tabulka, do kterého bude vložen nový záznam.
 * @param item Vkládaný záznam.
 * @param spam_or_ham 0 je spam, 1 je ham.
 * @return int 1 pokud vše dopadlo dobře, jinak 0.
 */
int hashtable_insert(hashtable* table, char* key, int spam_or_ham);

/**
 * @brief Funkce pro nalezení záznamu v tabulce.
 * @param table Tabulka, ve které bude hledán prvek.
 * @param item Hledaný záznam.
 * @return item* Ukazatel na hledaný prvek, pokud není nalezen tak vrátí NULL.
 */
item* hashtable_find(hashtable* table, char* key);

/**
 * @brief Funkce pro uvolnění struktury záznamu v tabulce.
 * @param item Ukazatel na ukazatel na záznamu, který bude uvolněn.
 */
void item_free(item** item);

/**
 * @brief Funkce pro uvolnění tabulkové struktury z paměti.
 * @param table Ukazatel na ukazatel na tabulky, která bude uvolněna.
 */
void hashtable_free(hashtable** table);


/**
 * @brief Funkce pro výpis celé tabulky.
 * @param table Ukazatel na tabulku, která bude vypsána.
 */
void hastable_print(hashtable* table);

/**
 * @brief Funkce pro přičt.
 * @param table Ukazatel na tabulku, která bude vypsána.
 */
void add_cont(item* it, int spam_or_ham);


#endif