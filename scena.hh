#ifndef SCENA_HH
#define SCENA_HH

/*!
 * \file
 * \brief Definicja klasy Scena
 *  
 * Plik zawiera definicję klasy Scena
 */

#include "powierzchnia_wody.hh"
#include "powierzchnia_dna.hh"
#include "dron.hh"
#include "lacze_do_gnuplota.hh"
#include <fstream>

/*!
 * \brief Modeluje pojęcie sceny, której
 * cechami są jej powierzchnie wody i dna 
 * oraz dron.
 */

class Scena {

Powierzchnia_wody _Pwody;

Powierzchnia_dna _Pdna;

public:

Dron _Dron;

/*!
 * \brief Inicjalizuje pola _Punkty_lokalne obiektów _Pwody i _Pdna.
 */ 
Scena ();

/*!
 * \brief Zapisuje _Punkty_lokalne obiektów _Pwody i _Pdna oraz 
 * _Punkty_globalne obiektu _Dron do odpowiedniego pliku.
 */
void stworz (std::string nazwa_pliku);

/*!
 * \brief Wykonuje rysunek wcześniej zapisanej sceny w
 * korzystając z programu gnuplot.
 */ 
void rysuj (PzG::LaczeDoGNUPlota Lacze) const;

};

#endif