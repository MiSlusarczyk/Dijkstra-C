/** @file  */

#pragma once

#include "structures.h"
#include "Lists.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
Glowna funkcja w ktorej wywolywane sa funkcje skladowe

@param path1 Pierwsza sciezka wejsciowa
@param path2 Druga sciezka wejsciowa
@param path3 Sciezka pliku wyjsciowego

@return Zwraca poprawnosc wykonania funkcji
*/
bool Management(const char* path1, const char* path2, const char* path3);


/**
Funkcja do odczytu danych

@param path1 Pierwsza sciezka wejsciowa
@param d_S Podwojny wskaznik do listy bramek 
@param d_CI Podwojny wskaznik do listy wejsc z pierwszego pliku
@param d_O Podwojny wskaznik do listy wyjsc
@param d_ST Podwojny wskaznik do listy stanu

@return Zwraca poprawnosc wykonania funkcji
*/
bool Load1(const char* path1, struct System** d_S, struct Node** d_CI, struct Node** d_O, struct Node** d_ST);
/**
Funkcja do odczytu danych

@param path2 Druga sciezka wejsciowa
@param d_CI Podwojny wskaznik do listy wejsc z pierwszego pliku
@param d_I Podwojny wskaznik do listy wyjsciowej
@param d_ST Podwojny wskaznik do listy stanu

@return Zwraca poprawnosc wykonania funkcji
*/
bool Load2(const char* path2, struct Node** d_CI, struct Input** d_I, struct Node** d_ST);
/**
Funkcja do zapisu rozwiazania do pliku

@param path3 Sciezka wyjsciowa
@param pHeadI Wskaznik do listy wejsc
@param pHeadO Wskaznik do listy wyjsc
@param pHeadSOL Wskaznik do listy rowiazan

@return Zwraca poprawnosc wykonania funkcji
*/
bool Save(const char* path3, struct Input* pHeadI, struct Node* pHeadO, struct Solution* pHeadSOL);

/**
Funkcje do odpowiedniego przypisania wczytanych danych

@param path2 Druga sciezka wejsciowa
@param file Zmienna odpowiedzialna za strumien do pliku
@param d_ST Podwojny wskaznik do listy stanu
@param d_O Podwojny wskaznik do listy wyjsc
@param d_S Podwojny wskaznik do listy bramek
@param d_CI Podwojny wskaznik do listy wejsc z pierwszego pliku
@param i Odczytane z pliku wejsciowego id bramki
*/
void Attribution(FILE* file, Node** d_ST, Node** d_O, System** d_S, Node** d_CI, Type type_name, int i);
/**
Funkcja do odpowiedniego przygotowania danych do rowiazania problemu

@param d_I Podwojny wskaznik do listy wyjsciowej
@param d_ST Podwojny wskaznik do listy stanu
@param d_SOL Podwojny wskaznik do listy rozwiazan
*/
bool CompleteData(Input* d_I, Node** d_ST, Solution** d_SOL);
/**
Funkcja sluzaca do rozwiazania problemu

@param d_S Podwojny wskaznik do listy bramek
@param d_SOL Podwojny wskaznik do listy rozwiazan
*/
void MakeSolution(System** d_S, Solution** d_SOL);
/**
Funkcja pomocnicza do rowiazania fragmentu problemu

@param tempS Lista bramek
@param d_tempLST Tymczasowa lista rozwiazan fragmentu problemu
*/
void SolveStep(System* tempS, Solution** d_tempLST);
/**
Funkcja pomocnicza do przypisania rozwiazania problemu
@param tempST Wskaznik do listy rozwiazan fragmentu problemu
@param pHeadST Wskaznik do listy stanu  do ktorego ma byc przypisany tempST
*/
void CompleteStep(Node* tempST, Node** pHeadST);

/**
Funkcja do wyswietlania rozwiazania

@param pHeadS Wskaznik do listy vramek
@param pHeadState Wskaznik do listy stanow
@param pHeadCI Wskaznik do listy wejsc z pierwszego pliku
@param pHeadI Wskaznik do listy wejsc
@param pHeadO Wskaznik do listy wyjsc
@param pHeadSOL Wskaznik do listy rowiazan
*/
void ShowAll(struct System* pHeadS, struct Node* pHeadState, struct Node* pHeadCI, struct Input* pHeadI, struct Node* pHeadO, struct Solution* pHeadSOL);