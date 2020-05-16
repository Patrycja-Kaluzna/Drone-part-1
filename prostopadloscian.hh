#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include "powierzchnia.hh"
#include "SMacierz.hh"
#include <cmath>

typedef SMacierz <double, 3> Macierz3x3;

class Prostopadloscian: public Powierzchnia {

    private:

    double _Kat_orientacji;

    Wektor3D _Wektor_translacji;

    Macierz3x3 _Macierz_rotacji;

    public: 

    Prostopadloscian ();

    void wczytaj_globalne ();

    void ustaw_Kat_orientacji (const double kat);

    void ustaw_Macierz_rotacji_OZ ();

    Wektor3D oblicz_Wektor_przemieszczenia (const double odleglosc);   

    void zmiana_orientacji_OZ (const double kat);

    void ruch_na_wprost (const double odleglosc); 

    void zapisz_globalne (std::string nazwa_pliku) const;

};

#endif