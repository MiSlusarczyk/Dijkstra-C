/** @file  */

#pragma once

#include "Structures.h"
#include "Functions.h"

#include <stdio.h>
#include <string.h>

/**
Funkcja do tworzenia domyslnej struktury wezla
*/
Node* CreateNode();
/**
Funkcja do tworzenia domyslnej struktury wejscia
*/
Input* CreateInput();
/**
Funkcja do tworzenia domyslnej struktury bramki
*/
System* CreateSystem();
/**
Funkcja do tworzenia domyslnej struktury pomocniczej do listy typu Int
*/
LInt* CreateLInt();
/**
Funkcja do tworzenia domyslnej struktury rozwiazania
*/
Solution* CreateSolution();

/**
Funkcja dodajaca wezel na koniec
*/
void AddNodeEnd(Node* n, Node** pHeadN);
/**
Funkcja kopiujaca wezel na koniec
*/
void CopyNodeEnd(Node* n, Node** pHeadN);
/**
Funkcja kopiujaca liste wezlow
*/
void CopyNodeList(Node* pHeadN1, Node** pHeadN2);
/**
Funkcja wyswietlajaca wezel
*/
void ShowNode(Node* pHeadN);
/**
Funkcja porownujaca wezly
*/
bool CompareNode(Node* pHeadI, Node* pHeadCI);
/**
Funkcja znajdujaca wezel po ID
*/
bool FindNodeID(unsigned int id, Node* pHeadN);
/**
Funkcja znajdujaca konkretny wezel w liscie
*/
Node* FindNodeN(Node* n, Node** pHeadState);
/**
Funkcja Funkcja znajdujaca konkretny wezel w liscie, zwrcajaca wartosc wezla
*/
char FindNodeVAL(unsigned int tempid, Node* pHeadN);
/**
Funkcja Funkcja znajdujaca konkretny wezel w liscie, i wyswietlajaca jego dane
*/
void PrintNode(Node* n, Node* pHeadN);



/**
Funkcja dodajaca bramke na koniec
*/
void AddSystemEnd(System* s, System** pHeadS);
/**
Funkcja wyswietlajaca liste bramek
*/
void ShowSystem(System* pHeadS);


/**
Funkcja dodajaca wejscie na koniec
*/
void AddInputEnd(Input* i, Input** pHeadI);
/**
Funkcja wyswietlajaca liste wejsc
*/
void ShowInput(Input* pHeadI);

/**
Funkcja kopiujaca element LInt na koniec listy
*/
void CopyLIntEnd(unsigned int n, LInt** pHeadLInt);
/**
Funkcja wyswietlajaca liste LInt
*/
bool FindLGate(unsigned int gid, LInt* pHeadLInt);

/**
Funkcja kopiujaca wejscie na koniec
*/
void AddSolutionEnd(Solution* sol, Solution** pHeadSOL);
/**
Funkcja wyswietlajaca liste rozwiazan
*/
void ShowSolution(Input* pHeadI, Node* pHeadO, Solution* pHeadSOL);