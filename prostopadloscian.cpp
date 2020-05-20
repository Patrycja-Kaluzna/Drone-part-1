#include "prostopadloscian.hh"



/*!
 * Inicjalizuje pole _Kat_orientacji wartością 0, oblicza i 
 * inicjalizuje pole _Macierz_rotacji oraz inicjalizuje pole 
 * _Wektor_translacji wartościami (10,10,25).
 */
Prostopadloscian::Prostopadloscian ()
{
    _Kat_orientacji = 0;
    ustaw_Macierz_rotacji_OZ();
    _Wektor_translacji[0] = 10; _Wektor_translacji[1] = 10; _Wektor_translacji[2] = 25;
}



/*!
 * Wczytuje zbiór punktów w globalnym układzie odniesienia,
 * przepisując je z kontenera zawierającego punkty lokalne
 * z dodanym do nich wektorem translacji.
 */
void Prostopadloscian::wczytaj_globalne ()
{
    unsigned int i;

    for (i = 0; i < _Punkty_lokalne.size(); ++i)
    {
        _Punkty_globalne.push_back(_Punkty_lokalne[i] + _Wektor_translacji);    
    }
}



/*!
 * Ustawia wartość pola _Kat_orientacji na zadaną parametrem.
 * \param [in] kat - wartość kąta, która zostanie ustawiona.
 * \pre Wartość kąta przekazywana przez parametr kat powinna
 *      zostać podana w stopniach (metoda przelicza ją na 
 *      radiany). 
 */
void Prostopadloscian::ustaw_Kat_orientacji (const double kat)
{
    _Kat_orientacji += (kat * 3.14 / 180);
}



/*!
 * Ustawia wartość pola _Macierz_rotacji na macierz macierz
 * obrotu wokół osi Z, a za kąt przyjmuje wartość pola
 * _Kat_orientacji.
 */
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



/*!
 * Oblicza wektor przemieszczenia o zadaną odległość w zależności
 * od orientacji prostopadłościanu oraz przelicza i ustawia 
 * odpowiednio wartość pola _Wektor_translacji.
 * \param [in] odleglosc - odległość, na którą  ma przemieścić się
 *          prostopadłościan.
 * \return Zwraca obliczony wektor przemieszczenia.
 */
Wektor3D Prostopadloscian::oblicz_Wektor_przemieszczenia (const double odleglosc)
{
    Wektor3D Wektor_przemieszczenia;

    Wektor_przemieszczenia[0] = odleglosc * cos(_Kat_orientacji + 90 * 3.14 / 180);   
    Wektor_przemieszczenia[1] = odleglosc * sin(_Kat_orientacji + 90 * 3.14 / 180);  
    Wektor_przemieszczenia[2] = 0;
    _Wektor_translacji = _Wektor_translacji + _Macierz_rotacji * Wektor_przemieszczenia;

    return Wektor_przemieszczenia;
}



/*!
 * Obraca prostopadłościan wokół osi Z o kąt przekazany przez
 * parametr ustawiając też wartość pola _Kat_orientacji oraz 
 * _Macierz_rotacji.
 * \param [in] kat - kąt, o który ma być obrócony prostopadłościan.
 */
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



/*!
 * Porusza prostopadłościan na wprost na zadaną odległość
 * obliczając odpowiedni wektor przemieszczenia.
 * \param [in] odleglosc - odległość, na którą ma przmieścić
 *          się prostopadłościan
 */
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



/*!
 * Umożliwia dostęp do kontenera z punktami globalnymi. 
 * \return Zwraca iterator pozwalający na czytanie zawartości
 *          kontenera.
 */
std::vector<Wektor3D>::const_iterator Prostopadloscian::get_Punkty_globalne () const
{
    std::vector<Wektor3D>::const_iterator I = _Punkty_globalne.begin();

    return I;
}



/*!
 * Zwraca liczbę elementów kontenera z puntkami globalnymi.
 * \return Zwraca liczbę elementów kontenera z puntkami globalnymi.
 */
unsigned int Prostopadloscian::liczba_Punktow_globalnych () const
{
    int pom;

    pom = _Punkty_globalne.size();

    return pom;
}



/*!
 * Zapisuje na strumieniu plikowym zbiór punktów w globalnym 
 * układzie odniesienia.
 * \param [in] Fstr - strumień plikowy, na którym zostaną
 *                    zapisane punkty globalne.
 * \param [in] Pro - protostopadłościan, którego punkty 
 *                   globalne zostaną zapisane.
 * \pre Fstr i Pro muszą być przekazane przez referencję.
 * \return Zwraca strumień plikowy.
 */
std::ofstream & operator << (std::ofstream & Fstr, const Prostopadloscian & Pro)
{
    std::vector<Wektor3D>::const_iterator I = Pro.get_Punkty_globalne();
    unsigned int i, pom = Pro.liczba_Punktow_globalnych();

    for (i = 0; i < pom; ++i)
    {
        if (i != (pom - 1))
        {
            Fstr << *I << "\n";
            ++I;
        } else {
            Fstr << *I;
        }
    }    

    return Fstr;
}