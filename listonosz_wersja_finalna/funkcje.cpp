/** @file */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>

#include"funkcje.h"
#include "struktury.h"


bool Pobranie_Argumentow(int& ile, char** arg, string& strIN, string& strOUT, int& poczatek)
{
    int const liczba_argumentow = 7;
    if (ile == liczba_argumentow)
    {
        for (int i = 1; i < ile; i += 2)
        {
            string temp = arg[i];
            if (temp == "-i")
            {
                if (strIN == "")
                    strIN = arg[i + 1];
                else
                {
                    cout << "Podano argument (-i plik wejsciowy) dwa razy" << endl;
                    return false;
                }
            }
            else if (temp == "-o")
            {
                if (strOUT == "")
                    strOUT = arg[i + 1];
                else
                {
                    cout << "Podano argument (-o plik wyjsciowy) dwa razy" << endl;
                    return false;
                }
            }
            else if (temp == "-p")
            {
                if (poczatek == NULL)
                {
                    stringstream ss;
                    ss << arg[i + 1];
                    if (ss >> poczatek);
                    else
                    {
                        cout << "Poczatek musi byc typu int" << endl;
                        return false;
                    }


                }
                else
                {
                    cout << "Podano argument (-p punkt startowy) dwa razy" << endl;
                    return false;
                }


            }
            else
            {
                //instrukcja
                cout << "Blad argumentow, brak flag(-i, -o, -p)" << endl;
                return false;
            }

        }

        if (strIN == strOUT)
        {
            cout << "Dla bezpieczenstwa twoich danych plik wejsciowy nie powinnien byc jednoczesnie plikiem wynikowym." << endl;
            return false;
        }

        return true;
    }
    else
    {
        cout << "Nie odpowiednia ilosc argumentow (" << ile - 1 << "/6)." << endl;
        cout << endl;
        cout << "Instrukcja : " << endl;
        cout << "Program uruchamiany jest z linii polecen z wykorzystaniem nastepujacych przelacznikow:"<<endl;
        cout << "\'-i\' plik wejsciowy "<<endl<<"\'-o\' plik wyjsciowy" << endl << "\'-p\' punkt startowy(numer skrzyzowania)" << endl;
        return false;
    }

}

vector<int> Sasiad(int& u, vector<krawendz>& g)
{
    vector<int> S;
    for (int i = 0; i < g.size(); i++)
    {
        if ((g[i].w1 == u || g[i].w2 == u) && g[i].usunienta == false)
        {
            int w = g[i].w1 == u ? g[i].w2 : g[i].w1;
            S.push_back(w);
        }
    }
    return S;
}

bool Pobranie_Danych(string& str, vector<krawendz>& Tgraf)
{
    ifstream input(str);
    string temp;
    if (input.good())
    {
        while (input.good())
        {
            krawendz tempK;
            getline(input, temp);
            if (temp == "")
            {
                if (input.good())continue;
                else break;
            }
            istringstream is(temp);
            if (is >> tempK.w1 >> tempK.w2 >> tempK.dl >> tempK.Nazwa)
            {
                string s;
                while (is >> s)
                {
                    tempK.Nazwa += " " + s;
                }
                Tgraf.push_back(tempK);
            }
            else
            {
                input.close();
                return false;
            }

        }
        input.close();
        return true;
    }
    else
    {
        input.close();
        return false;
    }

}

map<int, int> Stopnie(vector<krawendz>& vec)
{
    map<int, int> stopnie_wierzcholkow;
    for (int i = 0; i < vec.size(); i++)
    {
        stopnie_wierzcholkow[vec[i].w1]++;
        stopnie_wierzcholkow[vec[i].w2]++;
    }
    return stopnie_wierzcholkow;
}

bool Sprawdz_Euler(map<int, int>& m)
{
    for (auto& element : m)
    {
        if (m[element.first] % 2 != 0)
            return false;
    }
    return true;
}

bool Czy_spojny(vector<krawendz>& g, map<int, int>& m)
{
    map<int, bool> visited;
    int vc = 0;
    for (auto& element : m)
    {
        if (element.second > 0)
            visited[element.first] = false;
        else
        {
            visited[element.first] = true;
            vc++;
        }


    }
    stack<int> Stos;

    for (auto& element : visited)
    {
        if (visited[element.first] == false)
        {
            Stos.push(element.first);
            visited[element.first] = true;
            break;
        }
    }

    while (Stos.empty() == false)
    {
        int v;
        v = Stos.top();
        Stos.pop();
        vc++;
        vector<int> S = Sasiad(v, g);
        for (int u : S)
        {
            if (visited[u] == true)
            {
                continue;
            }
            visited[u] = true;
            Stos.push(u);
        }

    }

    if (vc == m.size())
        return true;
    else
        return false;


}

vector<int> Droga_Eulera(vector<krawendz> g, map<int, int> m, int& p)
{
    vector<int> droga;
    droga.push_back(p);
    int v = p;
    while (m[v] > 0)
    {
        if (m[v] == 1)
        {
            int w;
            for (int i = 0; i < g.size(); i++)
            {
                if ((g[i].w1 == v || g[i].w2 == v) && g[i].usunienta == false)
                {
                    w = g[i].w1 == v ? g[i].w2 : g[i].w1;
                    g[i].usunienta = true;
                    m[v] = 0;
                    m[w]--;
                    droga.push_back(w);
                    v = w;
                    break;
                }
            }
        }
        else
        {
            int w;
            for (int i = 0; i < g.size(); i++)
            {
                if ((g[i].w1 == v || g[i].w2 == v) && g[i].usunienta == false)
                {
                    w = g[i].w1 == v ? g[i].w2 : g[i].w1;
                    g[i].usunienta = true;
                    if ((Czy_spojny(g, m)))
                    {
                        if (m[w] == 1)
                        {
                            g[i].usunienta = false;
                        }
                        else
                        {
                            g[i].usunienta = true;
                            m[v]--;
                            m[w]--;
                            droga.push_back(w);
                            v = w;
                            break;
                        }
                    }
                    else
                    {
                        g[i].usunienta = false;
                    }

                }
            }
        }
    }
    return droga;
}

double Dlugosc(vector<krawendz>& g, int& u, int& w )
{
    double wynik = 0;
    for (int i = 0; i < g.size(); i++)
    {
        if (((g[i].w1 == u) && (g[i].w2 == w)) || ((g[i].w1 == w) && (g[i].w2 == u)))
        {
            wynik = g[i].dl;
            break;
        }
    }
    return wynik;
}

sciezka Dijkstra(vector<krawendz>& g, map<int, int>& m, int& v, int& k)
{
    double const INF = numeric_limits<double>::infinity();
    map<int, bool> Q, S;
    map<int, int> p;
    map<int, double> d;
    for (auto& element : m)
    {
        Q[element.first] = true;
        S[element.first] = false;
        d[element.first] = INF;
        p[element.first] = -1;
    }

    d[v] = 0;
    bool czyQmaWieszcholki = false;

    do
    {
        double min_d = INF;
        int u = 0;
        for (auto& element : m)
        {
            if ((d[element.first] < min_d) && (Q[element.first] == true))
            {
                min_d = d[element.first];
                u = element.first;
            }
        }
        Q[u] = false;
        S[u] = true;
        vector<int> Sasiadzi = Sasiad(u, g);

        for (int i = 0; i < Sasiadzi.size(); i++)
        {
            int w = Sasiadzi[i];

            if (Q[w] == true)
            {
                double dlogosc = Dlugosc(g,u, w);
                if (d[w] > (d[u] + dlogosc))
                {
                    d[w] = d[u] + dlogosc;
                    p[w] = u;
                }
            }
        }

        czyQmaWieszcholki = false;
        for (auto& element : m)
        {
            if (Q[element.first] == true)
            {
                czyQmaWieszcholki = true;
                break;
            }

        }
    } while (czyQmaWieszcholki);

    sciezka wynik;
    wynik.dl = d[k];
    int z = k;
    vector<int>droga;
    droga.push_back(k);
    while (p[z] != -1)
    {
        droga.push_back(p[z]);
        z = p[z];
    }
    wynik.droga = droga;
    return wynik;


}

vector<vector<kombinacja>> Generowanie_Kombinacji(int& k, vector<int>& vec)
{
    vector<vector<kombinacja>> wynik;
    for (int i = 0; i < k - 1; i++)
    {
        kombinacja para;
        para.w1 = vec[0];
        para.w2 = vec[i + 1];

        if (k > 2)
        {
            //stworzenie nowego vectora na int przekazywane
            vector<int> vec2;
            for (int j = 1; j < vec.size(); j++)
            {
                if (j != i + 1)
                {
                    vec2.push_back(vec[j]);
                }
            }
            int Nk = k - 2;
            vector<vector<kombinacja>> kombo= Generowanie_Kombinacji(Nk, vec2);

            for (int y = 0; y < kombo.size(); y++)
            {
                vector<kombinacja> vecK;
                vecK.push_back(para);
                for (int z = 0; z < kombo[y].size(); z++)
                {
                    vecK.push_back(kombo[y][z]);
                }
                wynik.push_back(vecK);
            }


        }
        else {
            vector<kombinacja> vecK;
            vecK.push_back(para);
            wynik.push_back(vecK);
            return wynik;
        }
    }
    return wynik;
}

void Dopisz(vector<krawendz>& g, map<int, int>& m, vector<kombinacja>& rozw)
{
    for (auto& pol : rozw)
    {
        sciezka dodatkowa = Dijkstra(g, m, pol.w1, pol.w2);
        for (int j = 0; j < dodatkowa.droga.size() - 1; j++)
        {
            for (int i = 0; i < g.size(); i++)
            {
                //sprawdzenie dl do dodania
                if (((g[i].w1 == dodatkowa.droga[j]) && (g[i].w2 == dodatkowa.droga[j + 1])) || ((g[i].w1 == dodatkowa.droga[j + 1]) && (g[i].w2 == dodatkowa.droga[j])))
                {
                    krawendz dd;
                    dd.w1 = dodatkowa.droga[j];
                    dd.w2 = dodatkowa.droga[j + 1];
                    dd.dl = g[i].dl;
                    dd.Nazwa = g[i].Nazwa;
                    g.push_back(dd);
                    m[dodatkowa.droga[j]]++;
                    m[dodatkowa.droga[j + 1]]++;
                    break;
                }
            }
        }
    }
}

void Naprawa(vector<krawendz>& g, map<int, int>& m)
{
    vector<int> nieparzyste;
    for (auto& element : m)
    {
        if (m[element.first] % 2 == 1)
            nieparzyste.push_back(element.first);
    }

    if (nieparzyste.size() == 2)
    {
        vector<kombinacja>rozw;
        kombinacja roz;
        roz.w1 = nieparzyste[0];
        roz.w2 = nieparzyste[1];
        rozw.push_back(roz);
        Dopisz(g, m, rozw);


    }
    else
    {

        int k = nieparzyste.size();
        vector<int> dokomb;
        for (int i = 0; i < k; i++)
        {
            dokomb.push_back(i);
        }

        vector<vector<kombinacja>> mozliwosci = Generowanie_Kombinacji(k, dokomb);
        int najlepsza_opcja = 0;

        double naj_dl = numeric_limits<double>::infinity();;
        double dl = 0;
        for (int i = 0; i < mozliwosci.size(); i++)
        {
            dl = 0;
            for (auto& element : mozliwosci[i])
            {
                sciezka dodatkowa = Dijkstra(g, m, nieparzyste[element.w1], nieparzyste[element.w2]);
                dl += dodatkowa.dl;
            }

            if (dl < naj_dl)
            {
                najlepsza_opcja = i;
                naj_dl = dl;
            }
        }
        vector<kombinacja>rozw = mozliwosci[najlepsza_opcja];
        for (auto& element : rozw)
        {
            int temp = element.w1;
            element.w1 = nieparzyste[temp];
            temp = element.w2;
            element.w2 = nieparzyste[temp];
        }
        Dopisz(g, m, rozw);
    }



}

string Nazwa_ulicy(vector<krawendz>& g, int& x, int& y)
{
    string nazwa = "";
    for (int i = 0; i < g.size(); i++)
    {
        if (((g[i].w1 == x) && (g[i].w2 == y)) || ((g[i].w1 == y) && (g[i].w2 == x)))
        {
            nazwa = g[i].Nazwa;
        }
    }
    return nazwa;
}

bool Czy_Nalezy_Do_Grafu(map<int, int>& m, int& v)
{
    for (auto& element : m)
    {
        if (element.first == v)
            return true;
    }
    return false;
}

void Przekaz_Wynik(vector<krawendz>& g, string& strOUT, vector<int>& DE)
{
    ofstream output(strOUT);
    if (output.good())
    {
        for (int i = 0; i < DE.size() - 1; i++)
        {
            output << DE[i] << " " << DE[i + 1] << " " << Nazwa_ulicy(g, DE[i], DE[i + 1]) << endl;
        }
        cout << "Wynik przekazany do pliku wynikowego" << endl;
    }
    else
    {
        cout << "Blad pliku wyjsciowgo" << endl;
    }
    output.close();
}
