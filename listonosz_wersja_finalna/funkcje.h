/** @file */
#pragma once
#ifndef FUNKCJE_H

#define FUNKCJE_H

#include<map>
#include "struktury.h"

/** Funkcja przekazująca parametry funkcji main do odpowiednich zmiennych.
 @param ile liczba parametrów przekazanych funkcji main
 @param arg tablica napisów reprezentujących parametry funkcji main
 @param strIN zmienna do której zostanie przekazany parametr po fladze '-i' (ścieżka do pliku wejściowego)
 @param strOUT zmienna do której zostanie przekazany parametr po fladze '-o' (ścieżka do pliku wyjściowego)
 @param poczatek zmienna do której zostanie przekazany parametr po fladze '-p' (punkt startowy)
 @return Jeśli operacja przebiegnie poprawnie zwraca wartość true, w razie wystąpienia jakiegokolwiek błędu wyświetla odpowiedni komunikat i zwraca wartość false.
 */
bool Pobranie_Argumentow(int& ile, char** arg, string& strIN, string& strOUT, int& poczatek);

/** Funkcja zwraca numery sąsiadujących wierzchołków.
@param u numer wierzchołka, którego sąsiadów szukamy 
@param g graf w któreym szukamy sąsiadów wierzchołka u
@return Zwraca wektor przechowujący numery sąsiadujących wierzchołków.
 */
vector<int> Sasiad(int& u, vector<krawendz>& g);

/** Funkcja pobiera dane z pliku wejściowego i przekazuje je do odpowiedniej zmiennej.
@param str ścierzka do pliku wejściowego
@param Tgraf zmienna, do którego przekazane zostaną dane z plik wejściowego
@return Jeśli operacja przebiegnie poprawnie zwraca wartość true, w razie wystąpienia błędu zwraca wartość false.
 */
bool Pobranie_Danych(string& str, vector<krawendz>& Tgraf);

/** Funkcja wyznacza stopień każdego wierzchołka grafu.
@param vec zmienna przechowywująca graf
@return Zwraca zmienną typu 'map' przechwywującą dla każdego wierzchołka grafu jego stopień.
 */
map<int, int> Stopnie(vector<krawendz>& vec);

/** Funkcja sprawdza czy dla danego grafu można wyznaczyc drogę Eulera.
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
@return Jeśli jest możliwe wyznaczenie drogi Eulera to funkcja zwraca true, jeśli nie ma takiej możliwości zwraca wartość false.
 */
bool Sprawdz_Euler(map<int, int>& m);

/** Funkcja sprawdza spójność grafu.
@param g zmienna przechowywująca graf
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
@return Jeśli graf jest spójny to zwraca wartość true, jeśli nie to zwraca wartość false.
 */
bool Czy_spojny(vector<krawendz>& g, map<int, int>& m);

/** Funkcja wykorzystując algorytm Fleury'ego wyznacza drogę/obwód Eulera.
@param g zmienna przechowywująca graf
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
@param p zmienna przechowująca punkt początkowy
@return Zwraca drogę w postaci wektora kolejnych pokonywanych wierzchołków.
 */
vector<int> Droga_Eulera(vector<krawendz> g, map<int, int> m, int& p);

/** Funkcja zwracająca długość krawędzi łączącej podane wierzchołki w podanym grafie.
@param g zmienna przechowywująca graf
@param w wierzchołek grafu
@param u wierzchołek grafu
@return Zwraca długość szukanej krawędzi o ile istnieje w przeciwnym razie zwróci 0;
 */
double Dlugosc(vector<krawendz>& g, int& u, int& w);

/** Funkcja wykorzystując algorytm Dijkstry do  wyznaczenia najkrótrzego połączenia dwóch wierzchołków grafu.
@param g zmienna przechowywująca graf
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
@param v początkowy wierzchołek 
@param k końcowy wierzchołek
@return Zwraca zmienną typu 'sciezka' przechowywującą długość najkrótrzego połączenia oraz wektro kolejnych wierzchołków tego połączenia.
 */
sciezka Dijkstra(vector<krawendz>& g, map<int, int>& m, int& v, int& k);

/** Funkcja generuje możliwe kombinacje zbioru(kolejnych liczb całkowitych) o podanej wielkości w pary.
@param k wielkość podanego zbioru
@param vec podany zbiór
@return Zwraca wektor zawierający kolejne kombinacje przedstawione w postaci wektorów kombinacji(par).
 */
vector<vector<kombinacja>> Generowanie_Kombinacji(int& k, vector<int>& vec);

/**Funkcja dodaje/dopisuje do grafu podane połączenia(w postaci odpowiednich krawędzi).
@param g zmienna przechowywująca graf
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
@param rozw wektor kombinacji wierzchołków dla których chcemy dopisac połączenia
 */
void Dopisz(vector<krawendz>& g, map<int, int>& m, vector<kombinacja>& rozw);

/** Funkcja odpowiednio zmienia graf(dopisuje nadmiarowe krawędzie), by móc wyznaczyć w nim drogę/obwód Eulera
@param g zmienna przechowywująca graf
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
 */
void Naprawa(vector<krawendz>& g, map<int, int>& m);

/** Funkcja zwracająca nazwe krawędzi łączącej podane wierzchołki w podanym grafie.
@param g zmienna przechowywująca graf
@param x wierzchołek grafu
@param y wierzchołek grafu
@return Zwraca nazwe szukanej krawędzi o ile istnieje w przeciwnym razie zwróci ("");
 */
string Nazwa_ulicy(vector<krawendz>& g, int& x, int& y);

/** Funkcja sprawdza czy wierzchołek należy do grafu
@param m zmienna przechowywująca dla każdego wierzchołka grafu jego stopień
@param v sprawdzany wierzchołek
@return Jeśli sprawdzany wierzchołek należy do grafu funkcja zwraca wartość true, w przeciwnym razie zwraca wartość false.
 */
bool Czy_Nalezy_Do_Grafu(map<int, int>& m, int& v);

/** Funkcja przekazuje rozwiązanie do pliku wynikowego
@param g zmienna przechowywująca graf
@param strOUT ścieżka do pliku wynikowego
@param DE zmienna przechowująca w wektorze drogę/obwód Eulera w postaci kolejnych wierzchołków grafu
 */
void Przekaz_Wynik(vector<krawendz>& g, string& strOUT, vector<int>& DE);

#endif 