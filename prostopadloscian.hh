#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

/*!
 * \file
 * \brief Definicja klasy Prostopadloscian
 * 
 * Plik zawiera definicję klasy Prostopadloscian,
 * która jest klasą pochodną klasy Powierzchnia.
 */

#include "powierzchnia.hh"
#include "SMacierz.hh"
#include <cmath>

typedef SMacierz <double, 3> Macierz3x3;

/*!
 * \brief Modeluje pojęcie prostopadłościanu,
 * którego cechami są zbiory jego punktów
 * w lokalnym oraz globalnym układzie
 * odniesienia, a także wektor translacji 
 * oraz kąt orientacji w tych układach.
 */

class Prostopadloscian: public Powierzchnia {

double _Kat_orientacji;

Wektor3D _Wektor_translacji;

Macierz3x3 _Macierz_rotacji;

public: 

/*!
 * \brief Inicjalizuje pole _Kat_orientacji wartością 0, oblicza i 
 * inicjalizuje pole _Macierz_rotacji oraz inicjalizuje pole 
 * _Wektor_translacji wartościami (10,10,25).
 */
Prostopadloscian ();

/*!
 * \brief Wczytuje zbiór punktów w globalnym układzie odniesienia.
 */
void wczytaj_globalne ();

/*!
 * \brief Ustawia wartość pola _Kat_orientacji.
 */
void ustaw_Kat_orientacji (const double kat);

/*!
 * \brief Ustawia wartość pola _Macierz_rotacji.
 */
void ustaw_Macierz_rotacji_OZ ();

/*!
 * \brief Oblicza wektor przemieszczenia.
 */
Wektor3D oblicz_Wektor_przemieszczenia (const double odleglosc);   

/*!
 * \brief Obraca prostopadłościan wokół osi Z.
 */
void zmiana_orientacji_OZ (const double kat);

/*!
 * \brief Porusza prostopadłościan na wprost.
 */
void ruch_na_wprost (const double odleglosc);

/*!
 * \brief Umożliwia dostęp do kontenera z punktami globalnymi.
 */
std::vector<Wektor3D>::const_iterator get_Punkty_globalne () const;

/*!
 * \brief Zwraca liczbę elementów kontenera z puntkami globalnymi.
 */
unsigned int liczba_Punktow_globalnych () const;

};

/*!
 * \brief Zapisuje na strumieniu plikowym zbiór punktów
 *  w globalnym układzie odniesienia.
 */
std::ofstream & operator << (std::ofstream & Fstr, const Prostopadloscian & Pro);

#endif