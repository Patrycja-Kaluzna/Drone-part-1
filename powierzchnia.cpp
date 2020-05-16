#include "powierzchnia.hh"



void Powierzchnia::wczytaj_lokalne (std::string nazwa_pliku)
{
    std::fstream plik;
    Wektor3D pom;

    plik.open(nazwa_pliku, std::ios::in);
    if (plik.is_open())
    {
        while (plik.eof() == false)
        {
        plik >> pom;
        _Punkty_lokalne.push_back(pom);
        }
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku << " nie powiodło się." << std::endl; 
    }
    plik.close();
}