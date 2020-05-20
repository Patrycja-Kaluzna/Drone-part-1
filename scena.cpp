#include "scena.hh"



/*!
 * Inicjalizuje pola _Punkty_lokalne obiektów _Pwody i _Pdna.
 */ 
Scena::Scena ()
{
    std::vector<Wektor3D> * lokalne_wody = _Pwody.get_Punkty_lokalne();
    std::vector<Wektor3D> * lokalne_dna = _Pdna.get_Punkty_lokalne();
    std::ifstream plik;
    Wektor3D pomWek;

    plik.open("plaszczyzny/woda.dat", std::ios::in);
    if (plik.is_open())
    {       
        while (plik >> pomWek)
        {
            lokalne_wody->push_back(pomWek);
        }
    } else {
            std::cerr << "Błąd: otwarcie pliku woda.dat nie powiodło się." << std::endl; 
    }
    plik.close();

    plik.open("plaszczyzny/dno.dat", std::ios::in);
    if (plik.is_open())
    {       
        while (plik >> pomWek)
        {
            lokalne_dna->push_back(pomWek);
        }
    } else {
            std::cerr << "Błąd: otwarcie pliku dna.dat nie powiodło się." << std::endl; 
    }
    plik.close();
}



/*!
 * Zapisuje _Punkty_lokalne obiektów _Pwody i _Pdna oraz 
 * _Punkty_globalne obiektu _Dron do odpowiedniego pliku.
 * \param[in] nazwa_pliku - nazwa pliku, do którego
 *              zostaną zapisane dane.
 */ 
void Scena::stworz (std::string nazwa_pliku)
{
    std::vector<Wektor3D> * lokalne_wody = _Pwody.get_Punkty_lokalne();
    std::vector<Wektor3D> * lokalne_dna = _Pdna.get_Punkty_lokalne();
    std::vector<Wektor3D>::const_iterator globalne_drona = _Dron._Kadlub.get_Punkty_globalne();
    unsigned int liczba_pglobalynch_drona = _Dron._Kadlub.liczba_Punktow_globalnych();

    std::fstream plik;
    unsigned int i;

    plik.open(nazwa_pliku, std::ios::out);
    if (plik.is_open())
    {
        plik << "# DRON \n";
        for (i = 0; i < liczba_pglobalynch_drona; ++i)
        {
            plik << *globalne_drona << '\n';
            ++globalne_drona;
        }
        plik << "\n # POWIERZCHNIA WODY \n";
        for (i = 0; i < lokalne_wody->size(); ++i)
        {
            plik << (*lokalne_wody)[i] << '\n';
        }
        plik << "\n # POWIERZCHNIA DNA \n";
        for (i = 0; i < lokalne_dna->size(); ++i)
        {
            plik << (*lokalne_dna)[i] << '\n';
        }
    } else {
        std::cerr << "Błąd: otwarcie pliku " << nazwa_pliku << " nie powiodło się." << std::endl;
    }
    plik.close();
}



/*!
 * Wykonuje rysunek wcześniej zapisanej sceny w
 * korzystając z programu gnuplot.
 * \param[in] Lacze - łącze do programu gnuplot.
 */ 
void Scena::rysuj (PzG::LaczeDoGNUPlota Lacze) const
{
    Lacze.Rysuj();
}