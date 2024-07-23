/** @file */
#include <iostream>

#include"funkcje.h"

/** @param ile liczba parametrów wywołania funkcji main
    @param arg tablica napisów reprezentujących parametry
 */
int main(int ile, char** arg)
{
    string strIN = "";
    string strOUT = "";
    int poczatek = NULL;

    if (Pobranie_Argumentow(ile, arg, strIN, strOUT, poczatek))
    {
        vector<krawendz> graf;
        if (Pobranie_Danych(strIN, graf))
        {
            map<int, int> sw = Stopnie(graf);
            vector<int> DE;
            if (Czy_Nalezy_Do_Grafu(sw, poczatek))
            {
                if (Czy_spojny(graf, sw))
                {
                    if (Sprawdz_Euler(sw))
                    {
                        DE = Droga_Eulera(graf, sw, poczatek);
                    }
                    else
                    {
                        Naprawa(graf, sw);
                        DE = Droga_Eulera(graf, sw, poczatek);
                    }
                    Przekaz_Wynik(graf, strOUT, DE);
                }
                else
                {
                    cout << "Podany graf(siatka skrzyżowania) jest niespójny." << endl;
                }
            }
            else
            {
                cout << "Podany punkt startowy nie nalezy do grafu(siatka skrzyzowania)." << endl;
            }
        }
        else
        {
            cout << "Blad pliku wejsciowego, sprawdz czy istnieje i jest zgodny z zaleceniem : " << endl;
            cout << "Linia pliku : <nr skrzyzowania 1> <nr skrzyzowania 2> <Dlugosc ulicy> <Nazwa ulicy>" << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Pobranie argumentow sie nie powiodlo" << endl;
    }



    return 0;
}
