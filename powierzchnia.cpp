#include "powierzchnia.hh"



/*!
 * Pozwala na dostęp do kontenera zawierającego
 * zbiór punktów w lokalnym układzie odniesienia.
 * \return Zwraca wskaźnik na konterer zawierający
 *          punkty lokalne.
 */ 
std::vector<Wektor3D> * Powierzchnia::get_Punkty_lokalne ()
{
    std::vector<Wektor3D> * pomWsk = &_Punkty_lokalne;

    return pomWsk;
}



/*!
 * Wczytuje ze strumienia plikowego zbiór punktów
 * w lokalnym układzie odniesienia.
 * \param [in] Fstr - strumień plikowy, z którego
 *              zostaną wczytane punkty lokalne.
 * \param [in] Pow - powierzchnia, której punkty
 *              lokalne zostaną wczytane.
 * \pre Fstr i Pow muszą być przekazane przez 
 *              referencję.
 * \return Zwraca strumień plikowy.
 */
std::ifstream & operator >> (std::ifstream & Fstr, Powierzchnia & Pow)
{
    std::vector<Wektor3D> * pomWsk = Pow.get_Punkty_lokalne();
    Wektor3D pomWek;

    while (Fstr.eof() == false)
    {
        Fstr >> pomWek;
        pomWsk->push_back(pomWek);
    }

    return Fstr;
}