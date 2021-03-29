/** @file  */

#pragma once

#include <stdio.h>
#include <math.h>
/**
Zdefiniowany typ wlasny odpowiadajacy mozliwym typom bramki
*/
typedef enum Type { IN, OUT, NEG, AND, NAND, OR, NOR, XOR, XNOR, NA } Type;
/**
Zdefiniowany typ bool'a
*/
typedef enum bool{ false, true } bool;


/**
Struktura wezla
*/
typedef struct Node
{
	char val; ///< Atrybut odpowiadajacy mozliwemu stanowi wezla
	unsigned int id; ///< Atrybut okreslajacy id wezla
	struct Node* pNext; ///< Wskaznik na kolejny element listy

}Node;

/**
Struktura bramki
*/
typedef struct System
{
	unsigned int gid; ///<A trybut okreslajacy id bramki
	enum type gate; ///< Atrybut okreslajacy typ bramki
	struct Node* in; ///< Wskaznik do listy wejsc bramki
	struct Node* out; ///< Wskaznik do listy wyjsc bramki
	struct System* pNext; ///< Wskaznik na kolejny element listy

}System;

/**
Struktura wejscia
*/
typedef struct Input
{
	struct Node* i; ///< Lista wezlow wejscia
	int tact; //< Liczba taktow wejscia
	struct Input* pNext; ///< Wskaznik na kolejny element listy

} Input;

/**
Struktura listy intow
*/
typedef struct LInt
{
	int val; ///< Wartosc int elementu listy
	struct LInt* pNext; ///< Wskaznik na kolejny element listy

} LInt;

/**
Struktura rozwiazan
*/
typedef struct Solution
{
	struct Node* tempST; ///<Wskaznik do listy tymczasowej podczas okreslnia rowiazania
	struct LInt* lgate; ///<Wskaznik do listy tymczasowej podczas okreslnia rowiazania
	struct Node* ST; ///<Wskaznik do listy rozwiazan
	int tact; ///< Atrybut okreslajacy liczbe taktow w danym rozwiazaniu
	struct Solution* pNext; ///< Wskaznik na kolejny element listy

} Solution;