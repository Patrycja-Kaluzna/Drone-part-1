#ifndef SMACIERZ_HH
#define SMACIERZ_HH

#include "SWektor.hh"
#include <iostream>

/*
 * Szablon klasy modelujacej pojecie macierzy, ktorej
 * glowna cecha sa jej kolumny. Szablon jest 
 * parametryzowany typem liczb będących wspołrzędnymi
 * wektorow tworzacych kolumny oraz rozmiarem tych 
 * wektorow, czyli ilością ich współrzędnych.
 */
template <typename typ, int rozmiar> 
class SMacierz {
  
    SWektor <typ, rozmiar> kolumny [rozmiar];   // Kolumny macierzy
    
    public:

    typ operator () (unsigned int indeksK, unsigned int indeksW) const {   // Umozliwia czytanie elementow macierzy
    return kolumny[indeksK][indeksW];}

    typ & operator () (unsigned int indeksK, unsigned int indeksW) {   // Umozliwia wczytywanie elementow macierzy
    return kolumny[indeksK][indeksW];}

    SWektor <typ, rozmiar>  operator [] (unsigned int indeks) const {    // Umozliwia czytanie kolumn macierzy
    return kolumny[indeks];}

    SWektor <typ, rozmiar> & operator [] (unsigned int indeks) {    // Umozliwia wczytywanie kolumn macierzy
    return kolumny[indeks];}

    SMacierz elementy2 () const;   // Realizuje podnoszenie do kwadratu kazdego z elementow macierzy

    void zamien_kolumny (unsigned int indeks1, unsigned int indeks2);    // Realizuje zamiane ze soba kolumn macierzy

    typ oblicz_wyznacznik () const;   // Oblicza wyznacznik macierzy metoda eliminacji Gaussa

    SMacierz podmien_kolumne (unsigned int indeks, SWektor <typ, rozmiar> Wek) const;  // Realizuje podmiane kolumny macierzy z wektorem

    SMacierz transponuj () const;    // Realizuje transpozycje macierzy

    SWektor <typ, rozmiar> operator * (SWektor <typ, rozmiar> Wek) const;   // Realizuje mnozenie macierzy z wektorem
};

/*
 * Realizuje podnoszenie do kwadratu kazdego z elementow macierzy.
 */
template <typename typ, int rozmiar>
SMacierz <typ, rozmiar> SMacierz<typ, rozmiar>::elementy2 () const
{
   SWektor <typ, rozmiar> pomWek1, pomWek2;
   unsigned int i, j;
   SMacierz <typ, rozmiar> pomMac;
   typ pomdbl;

   for (i = 0; i < rozmiar; i++)
   {
        pomWek1 = kolumny[i];
        for (j = 0; j < rozmiar; j++)
        {
            pomdbl = pomWek1[j] * pomWek1[j];
            pomWek2[j] = pomdbl;
        }
        pomMac[i] = pomWek2;
   }

   return pomMac;
}



/*
 * Realizuje zamiane ze soba kolumn macierzy.
 */ 
template <typename typ, int rozmiar>
void SMacierz<typ, rozmiar>::zamien_kolumny (unsigned int indeks1, unsigned int indeks2)
{
    SWektor <typ, rozmiar> pomW;

    pomW = kolumny[indeks1];
    kolumny[indeks1] = kolumny[indeks2];
    kolumny[indeks2] = pomW;
}



/*
 * Oblicza wyznacznik macierzy metoda eliminacji Gaussa.
 */
template <typename typ, int rozmiar>
typ SMacierz<typ, rozmiar>::oblicz_wyznacznik () const
{
    unsigned int i, j, k, l, m;
    typ wyznacznik, mnoznik;
    SMacierz <typ, rozmiar> pomM;
    m = 0;
    wyznacznik = 1;
    pomM = *this;
    for (i = 0; i < (rozmiar - 1); ++i) {
        if (pomM(i,i) == 0) {
            for (l = i + 1; l < rozmiar; ++l) {
                while (pomM(i,i) == 0) {
                    if (pomM(l,i) != 0) {
                        pomM.zamien_kolumny(i,l);
                        m++; 
                    }    
                }
            }
            if (pomM(i,i) == 0) {
                std::cout << "Blad: macierz osobliwa" << std::endl;
                return wyznacznik;
            }    
        }
        for (j = i + 1; j < rozmiar; ++j) {
            mnoznik = pomM(j,i) / pomM(i,i) * -1;
            for (k = i; k < rozmiar; ++k) {
                pomM(j,k) += (mnoznik * pomM(i,k));                
            }   
        }    
    }
    for (i = 0; i < rozmiar; ++i) {
        wyznacznik = wyznacznik * pomM(i,i);
    }
    if (m % 2 == 0) {
        return wyznacznik;
    } else {
        wyznacznik = wyznacznik * -1;
        return wyznacznik;
    }
}



/*
 * Realizuje podmiane kolumny macierzy z wektorem.
 */
template <typename typ, int rozmiar>
SMacierz <typ, rozmiar> SMacierz<typ, rozmiar>::podmien_kolumne (unsigned int indeks, SWektor <typ, rozmiar> Wek) const
{
    SMacierz <typ, rozmiar> pomM;

    pomM = *this;
    pomM[indeks] = Wek;

    return pomM;
}



/*
 * Realizuje transpozycje macierzy.
 */ 
template <typename typ, int rozmiar>
SMacierz <typ, rozmiar> SMacierz<typ, rozmiar>::transponuj () const
{
    unsigned int i, j;
    SMacierz <typ, rozmiar> pomM;

    for (i = 0; i < rozmiar; ++i)
    {
        for (j = 0; j < rozmiar; ++j)
        {
            pomM(j,i) = kolumny[i][j];
        }
    }

    return pomM;
}



/*
 * Realizuje mnozenie macierzy z wektorem.
 */
template <typename typ, int rozmiar>
SWektor <typ, rozmiar> SMacierz<typ, rozmiar>::operator * (SWektor <typ, rozmiar> Wek) const
{
    unsigned int i, j;
    SMacierz <typ, rozmiar> pomM;
    SWektor <typ, rozmiar> pomW;

    pomM = *this;
    for (i = 0; i < rozmiar; ++i)
    {
        pomW[i] = 0;
        for (j = 0; j < rozmiar; ++j)
        {
            pomW[i] += pomM[i][j] * Wek[j];
        }
    }

    return pomW;
}



/*
 * Zapisuje kolumny macierzy na strumieniu wyjsciowym. 
 */
template <typename typ, int rozmiar>
std::ostream & operator << (std::ostream & Str, const SMacierz <typ, rozmiar> & Mac)
{
    unsigned int i;

    for (i = 0; i < rozmiar; ++i)
    {
        Str << Mac[i] << std::endl;
    }

    return Str;
}



/*
 * Wczytuje kolumny macierzy ze strumienia wejsciowego.
 */ 
template <typename typ, int rozmiar>
std::istream & operator >> (std::istream & Str, SMacierz <typ, rozmiar> & Mac)
{
    unsigned int i;
    SWektor <typ, rozmiar> pom;

    for (i = 0; i < rozmiar; ++i)
    {
        Str >> pom;
        Mac[i] = pom;
    }

    return Str;
}

#endif