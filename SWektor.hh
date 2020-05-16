#ifndef SWEKTOR_HH
#define SWEKTOR_HH

#include <iostream>
#include <cmath>

/*
 * Szablon klasy modelującej pojęcie wektora, którego
 * główną cechą są jego współrzędne. Szablon jest 
 * parametryzowany typem liczb będących wspołrzędnymi
 * wektora oraz rozmiarem wektora, czyli ilością jego
 * współrzędnych.
 */
template <typename typ, int rozmiar>
class SWektor {

    typ wspolrzedne [rozmiar];      // Wspolrzedne wektora
    
    //static int ilosc;

    public:

    //SWektor () {++ilosc;}

    //~SWektor () {--ilosc;}

    typ operator [] (unsigned int indeks) const {       // Umozliwia czytanie wspolrzednych wektora
        return wspolrzedne [indeks]; }

    typ & operator [] (unsigned int indeks) {       // Umozliwia wczytywanie wspolrzednych wektora
        return wspolrzedne [indeks]; }    

    SWektor <typ, rozmiar> operator + (const SWektor <typ, rozmiar> Wek) const;   // Realizuje dodawanie wektorow

    SWektor <typ, rozmiar> operator - (const SWektor <typ, rozmiar> Wek) const;   // Realizuje odejmowanie wektorow

    typ operator * (const SWektor <typ, rozmiar> Wek) const;   // Realizuje mnozenie (iloczyn skalarny) wektorow

    SWektor <typ, rozmiar> operator * (const double lic) const;   // Realizuje mnozenie wektora przez liczbe

    SWektor <typ, rozmiar> operator / (const double lic) const;   // Realizuje dzielenie wektora przez liczbe

    SWektor <typ, rozmiar> iloczyn_wektorowy (const SWektor <typ, rozmiar> Wek) const;    // Relizuje mnozenie (iloczyn
                                                                                          // wektorowy) wektorow
};



/*
 * Realizuje dodawanie wektorow
 */ 
template <typename typ, int rozmiar>
SWektor <typ, rozmiar> SWektor<typ, rozmiar>::operator + (const SWektor <typ, rozmiar> Wek) const
{
    unsigned int i;
    SWektor <typ, rozmiar> pomWek;
    
    for (i = 0; i < rozmiar; ++i)
    {
        pomWek[i] = wspolrzedne[i] + Wek[i];
    }

    return pomWek;
}



/*
 * Realizuje odejmowanie wektorow
 */ 
template <typename typ, int rozmiar>
SWektor <typ, rozmiar> SWektor<typ, rozmiar>::operator - (const SWektor <typ, rozmiar> Wek) const
{
    unsigned int i;
    SWektor <typ, rozmiar> pomWek;

    for (i = 0; i < rozmiar; ++i)
    {
        pomWek[i] = wspolrzedne[i] - Wek[i];
    }

    return pomWek;
}



/*
 * Realizuje mnozenie (iloczyn skalarny) wektorow
 */ 
template <typename typ, int rozmiar>
typ SWektor <typ, rozmiar>::operator * (const SWektor <typ, rozmiar> Wek) const
{
    unsigned int i;
    typ lic;
    lic = 0;

    for (i = 0; i < rozmiar; ++i)
    {
        lic += wspolrzedne[i] * Wek[i];
    }

    return lic;
}



/*
 * Realizuje mnozenie wektora przez liczbe
 */ 
template <typename typ, int rozmiar>
SWektor <typ, rozmiar> SWektor<typ, rozmiar>::operator * (const double lic) const
{
    unsigned int i;
    SWektor <typ, rozmiar> pomWek;

    for (i = 0; i < rozmiar; ++i)
    {
        pomWek[i] = wspolrzedne[i] * lic;
    }

    return pomWek;
}



/*
 * Realizuje dzielenie wektora przez liczbe
 */ 
template <typename typ, int rozmiar>
SWektor <typ, rozmiar> SWektor<typ, rozmiar>::operator / (const double lic) const
{
    unsigned int i;
    SWektor <typ, rozmiar> pomWek;

    if (lic != 0)
    {
        for (i = 0; i < rozmiar; ++i)
        {
            pomWek[i] = wspolrzedne[i] / lic;
        }
    } else {
        std::cout << "Blad: dzielenie przez zero." << std::endl;
    }

    return pomWek;
}



/*
 * Relizuje mnozenie (iloczyn wektorowy) wektorow
 */ 
template <typename typ, int rozmiar>
SWektor <typ, rozmiar> SWektor<typ, rozmiar>::iloczyn_wektorowy (const SWektor <typ, rozmiar> Wek) const
{
    unsigned int i = 0, j = 1, k = 2;
    SWektor <typ, rozmiar> pomWek;

    pomWek[i] = wspolrzedne[j] * Wek[k] - wspolrzedne[k] * Wek[j];
    pomWek[j] = (wspolrzedne[i] * Wek[k] - wspolrzedne[k] * Wek[i]) * -1;
    pomWek[k] = wspolrzedne[i] * Wek[j] - wspolrzedne[j] * Wek[i];

    return pomWek;
}



/*
 * Wczytuje wspolrzedne wektora ze strumienia wejsciowego.
 */
template <typename typ, int rozmiar>
std::istream & operator >> (std::istream & Str, SWektor <typ, rozmiar> & Wek)
{
    unsigned int i;

    for (i = 0; i < rozmiar; ++i)
    {
        Str >> Wek[i];
    }

    return Str;
}



/*
 * Zapisuje wspolrzedne wektora na strumieniu wyjsciowym.
 */
template <typename typ, int rozmiar>
std::ostream & operator << (std::ostream & Str, const SWektor <typ, rozmiar> & Wek)
{
    unsigned int i;

    for (i = 0; i < rozmiar; ++i) 
    {
        Str << Wek[i] << " ";
    }

    return Str;
}

#endif