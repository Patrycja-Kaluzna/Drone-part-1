#include "lacze_do_gnuplota.hh"
#include "dron.hh"

#include <unistd.h>
#include <iostream>
#include <iomanip>

using namespace std;



void wyswietl_menu ()
{
    cout << "Dostępne opcje:" << endl;
    cout << "m - powróć do menu opcji" << endl << "r - zadaj ruch na wprost" << endl;
    cout << "o - zadaj zmianę orientacji" << endl << "k - zakończ działanie programu" << endl;
}



void wyswietl_ilosc_Wektorow3D ()
{

}



int main ()
{
    PzG::LaczeDoGNUPlota Lacze;
    unsigned int i;
    char opcja;
    Dron Dron;
    
    Dron._Kadlub.wczytaj_lokalne("plaszczyzny/dron1.dat");
    Dron._Kadlub.wczytaj_globalne();
    Dron._Kadlub.zapisz_globalne("plaszczyzny/dron2.dat");

    Lacze.UsunWszystkieNazwyPlikow();
    Lacze.DodajNazwePliku("plaszczyzny/dron2.dat");

    Lacze.ZmienTrybRys(PzG::TR_3D);

    Lacze.Inicjalizuj();

    Lacze.UstawZakresX(-100, 100);
    Lacze.UstawZakresY(-100, 100);
    Lacze.UstawZakresZ(0, 150);
    Lacze.UstawRotacjeXZ(40, 60);

    Lacze.Rysuj();

    wyswietl_menu();
    wyswietl_ilosc_Wektorow3D();

    Dron._Kadlub.zmiana_orientacji_OZ(1);

    do {
        cin >> opcja;
        switch (opcja)
        {
            case 'm':
            {
                wyswietl_menu();
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            case 'r':
            {
                double odleglosc;
                cout << "Podaj odległość, na którą ma przemieścić się dron: ";
                cin >> odleglosc;
                for (i = 0; i < 5; ++i)
                {
                    Dron._Kadlub.ruch_na_wprost(odleglosc / 5);
                    Dron._Kadlub.zapisz_globalne("plaszczyzny/dron2.dat");
                    Lacze.Rysuj();
                    usleep(50000);
                }
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            case 'o':
            {
                double kat;
                cout << "Podaj kąt, o który ma obrócić się dron (w stopniach): ";
                cin >> kat;
                for (i = 0; i < 5; ++i)
                {
                    Dron._Kadlub.zmiana_orientacji_OZ(kat / 5);
                    Dron._Kadlub.zapisz_globalne("plaszczyzny/dron2.dat");
                    Lacze.Rysuj();
                    usleep(50000);
                }
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            case 'k':
            {
                cout << "Koniec działania programu" << endl;
                wyswietl_ilosc_Wektorow3D();
                break;
            }
            default:
            {
                cout << "Bład: niepoprawna opcja. Wybierz opcje jeszcze raz." << endl;
                break;
            }
        }
    } while (opcja != 'k');

    Lacze.UsunWszystkieNazwyPlikow();
}