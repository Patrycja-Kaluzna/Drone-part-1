#ifndef PLASZCZYZNA_HH
#define PLASZCZYZNA_HH

/*!
 * \file
 * \brief Definicja klasy Powierzchnia
 * 
 * Plik zawiera definicję klasy Powierzchnia,
 * która jest klasą bazową.
 */ 

#include "SWektor.hh"
#include <vector>
#include <fstream>

/*!
 * \brief Modeluje pojęcie powierzchni,
 * której cechami są zbiory jej punktów
 * w lokalnym oraz globalnym układzie
 * odniesienia.
 */ 

typedef SWektor <double, 3> Wektor3D;

class Powierzchnia {

protected:

std::vector <Wektor3D> _Punkty_lokalne;

std::vector <Wektor3D> _Punkty_globalne;
    
public:

/*!
 * \brief Pozwala na dostęp do kontenera zawieającego
 * zbiór punktów w lokalnym układzie odniesienia.
 */ 
std::vector<Wektor3D> * get_Punkty_lokalne ();

};

/*!
 * \brief Wczytuje ze strumienia plikowego zbiór punktów
 *  w lokalnym układzie odniesienia.
 */ 
std::ifstream & operator >> (std::ifstream & Fstr, Powierzchnia & Pow);

#endif