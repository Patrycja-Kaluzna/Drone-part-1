#ifndef PLASZCZYZNA_HH
#define PLASZCZYZNA_HH

#include "SWektor.hh"
#include <vector>
#include <fstream>

typedef SWektor <double, 3> Wektor3D;

class Powierzchnia {

    protected:

    std::vector <Wektor3D> _Punkty_lokalne;

    std::vector <Wektor3D> _Punkty_globalne;
    
    public:

    void wczytaj_lokalne (std::string nazwa_pliku);

};

#endif