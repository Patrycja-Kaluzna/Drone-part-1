#ifndef SWEKTOR_HH
#define SWEKTOR_HH

#include <iostream>
#include <cmath>

/*!
 * \brief Szablon klasy modelującej pojęcie wektora, 
 * którego główną cechą są jego współrzędne. Szablon 
 * jest  parametryzowany typem liczb będących 
 * wspołrzędnymi wektora oraz rozmiarem wektora, 
 * czyli ilością jego współrzędnych.
 */
template <typename typ, int rozmiar>
class SWektor {

    typ wspolrzedne [rozmiar];

    static unsigned int aktualna_ilosc;

    static unsigned int laczna_ilosc;

    public:

    /*!
     * \brief Inkrementuje aktualną i łączną ilość obiektów klasy SWektor.
     */ 
    SWektor () {
        ++aktualna_ilosc; ++laczna_ilosc;}

    /*!
     * \brief Inkrementuje aktualną i łączną ilość obiektów klasy SWektor.
     */ 
    SWektor (const SWektor<typ, rozmiar> & SWek) {
        *this = SWek; ++aktualna_ilosc; ++laczna_ilosc;}

    /*!
     * \brief Dekrementuje aktualną ilość obiektów klasy SWektor.
     */ 
    ~SWektor () {--aktualna_ilosc;}

    /*!
     * \brief Umożliwia czytanie aktualnej ilości obiektów klasy SWektor.
     */
    static unsigned int get_aktualna_ilosc () {return aktualna_ilosc;}

    /*!
     * \brief Umożliwia czytanie łącznej ilości obiektów klasy SWektor
     * powstałych w trakcie działania programu.
     */ 
    static unsigned int get_laczna_ilosc () {return laczna_ilosc;}

    /*!
     * \brief Umozliwia czytanie wspolrzednych wektora.
     */ 
    typ operator [] (unsigned int indeks) const {     
        return wspolrzedne [indeks]; }

    /*!
     * \brief Umozliwia wczytywanie wspolrzednych wektora.
     */ 
    typ & operator [] (unsigned int indeks) {   
        return wspolrzedne [indeks]; }    

    /*!
     * \brief Realizuje dodawanie wektorow.
     */ 
    SWektor <typ, rozmiar> operator + (const SWektor <typ, rozmiar> Wek) const;

    /*!
     * \brief Realizuje odejmowanie wektorow.
     */ 
    SWektor <typ, rozmiar> operator - (const SWektor <typ, rozmiar> Wek) const;

    /*!
     * \brief Realizuje mnozenie (iloczyn skalarny) wektorow.
     */ 
    typ operator * (const SWektor <typ, rozmiar> Wek) const;

    /*!
     * \brief Realizuje mnozenie wektora przez liczbe.
     */ 
    SWektor <typ, rozmiar> operator * (const double lic) const;

    /*!
     * \brief Realizuje dzielenie wektora przez liczbe.
     */ 
    SWektor <typ, rozmiar> operator / (const double lic) const;

    /*!
     * \brief Relizuje mnozenie (iloczyn wektorowy) wektorow.
     */ 
    SWektor <typ, rozmiar> iloczyn_wektorowy (const SWektor <typ, rozmiar> Wek) const;
                                                                                        
};



template <typename typ, int rozmiar>
unsigned int SWektor<typ, rozmiar>::aktualna_ilosc;



template <typename typ, int rozmiar>
unsigned int SWektor<typ, rozmiar>::laczna_ilosc;



/*!
 * \brief Realizuje dodawanie wektorow
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



/*!
 * \brief Realizuje odejmowanie wektorow
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



/*!
 * \brief Realizuje mnozenie (iloczyn skalarny) wektorow
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



/*!
 * \brief Realizuje mnozenie wektora przez liczbe
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



/*!
 * \brief Realizuje dzielenie wektora przez liczbe
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



/*!
 * \brief Relizuje mnozenie (iloczyn wektorowy) wektorow
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



/*!
 * \brief Wczytuje wspolrzedne wektora ze strumienia wejsciowego.
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



/*!
 * \brief Zapisuje wspolrzedne wektora na strumieniu wyjsciowym.
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