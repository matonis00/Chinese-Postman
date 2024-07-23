/** @file */
#pragma once
#ifndef STRUKTURY_H 
#define STRUKTURY_H


using namespace std;
#include<vector>
#include<string>

/**
Struktura opisująca krawędz grafu (pojedyńczą ulicę).
 */
struct krawendz
{
    int w1;                 /**< pierwszy wieszchołek */
    int w2;                 /**< drugi wieszchołek */
    double dl;              /**< długość krawędzi(ulicy) */
    string Nazwa = "";      /**< nazwa krawędzi(ulicy) */
    bool usunienta = false; /**< parametr bool wskazujacy czy krawędź została już wykorzystana */
};

/**
Struktura opisująca ścieżkę/drogę w grafie.
 */
struct sciezka
{
    double dl;          /**< długość całej ścieżki */
    vector<int> droga;  /**< vektor zawierający kolejne wierzchołki ścieżki */
};

/**
Struktura opisująca kombinacje (para zmiennych typu int).
 */
struct kombinacja {
    int w1; /**< pierwsza liczba w kombinacji (calkowita)*/
    int w2; /**< druga liczba w kombinacji (calkowita)*/
};

#endif 