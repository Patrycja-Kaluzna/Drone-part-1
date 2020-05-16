#include "prostopadloscian.hh"



Prostopadloscian::Prostopadloscian ()
{
    _Kat_orientacji = 0;
    _Wektor_translacji[0] = 10; _Wektor_translacji[1] = 10; _Wektor_translacji[2] = 0;
}



void Prostopadloscian::wczytaj_globalne ()
{
    unsigned int i;

    for (i = 0; i < _Punkty_lokalne.size(); ++i)
    {
        _Punkty_globalne.push_back(_Punkty_lokalne[i] + _Wektor_translacji);    
    }
}



void Prostopadloscian::ustaw_Kat_orientacji (const double kat)
{
    _Kat_orientacji += (kat * 3.14 / 180);
}



void Prostopadloscian::ustaw_Macierz_rotacji_OZ ()
{
    _Macierz_rotacji(0,0) = cos(_Kat_orientacji);
    _Macierz_rotacji(0,1) = -sin(_Kat_orientacji);
    _Macierz_rotacji(0,2) = 0;
    _Macierz_rotacji(1,0) = sin(_Kat_orientacji);
    _Macierz_rotacji(1,1) = cos(_Kat_orientacji);
    _Macierz_rotacji(1,2) = 0;
    _Macierz_rotacji(2,0) = 0;
    _Macierz_rotacji(2,1) = 0;
    _Macierz_rotacji(2,2) = 1;
}



Wektor3D Prostopadloscian::oblicz_Wektor_przemieszczenia (const double odleglosc)
{
    Wektor3D Wektor_przemieszczenia;

    Wektor_przemieszczenia[0] = odleglosc * cos(_Kat_orientacji + 90 * 3.14 / 180);
    Wektor_przemieszczenia[1] = odleglosc * sin(_Kat_orientacji + 90 * 3.14 / 180);
    Wektor_przemieszczenia[2] = 0;
    _Wektor_translacji = _Wektor_translacji + _Macierz_rotacji * Wektor_przemieszczenia;

    return Wektor_przemieszczenia;
}



void Prostopadloscian::zmiana_orientacji_OZ (const double kat)
{
    unsigned int i;

    ustaw_Kat_orientacji(kat);
    ustaw_Macierz_rotacji_OZ();
    for (i = 0; i < _Punkty_globalne.size(); ++i)
    { 
        _Punkty_globalne[i] = _Macierz_rotacji * _Punkty_lokalne[i] + _Wektor_translacji;
    }
}



void Prostopadloscian::ruch_na_wprost (const double odleglosc)
{
    unsigned int i;
    Wektor3D Wektor_przemieszczenia;

    Wektor_przemieszczenia = oblicz_Wektor_przemieszczenia(odleglosc);
    for (i = 0; i < _Punkty_globalne.size(); ++i)
    {
        _Punkty_globalne[i] = _Punkty_globalne[i] + _Macierz_rotacji * Wektor_przemieszczenia;
    }
}



void Prostopadloscian::zapisz_globalne (std::string nazwa_pliku) const
{
    std::fstream plik;
    unsigned int i;

    plik.open(nazwa_pliku, std::ios::out);
    if (plik.is_open())
    {
        for (i = 0; i < _Punkty_globalne.size(); ++i)
        {
            if (i != (_Punkty_globalne.size() - 1))
            {
                plik << _Punkty_globalne[i] << '\n'; 
            } else {
                plik << _Punkty_globalne[i];
            }
        }
    } else {
        std::cout << "Błąd: otwarcie pliku " << nazwa_pliku << " nie powiodło się." << std::endl;
    }
    plik.close();
}