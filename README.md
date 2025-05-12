Mini aplicatie de genul RateYourMusic, bazata pe publicarea de note si recenzii unor anumite obiecte muzicale, precum recenzii sau note.
Clasa principala ObiectMuzical are mostenirile Artist, Melodie si Album, si contine o functie virtuala de afisare a anumitor detalii despre fiecare obiect.
Exista posibilitatea de adaugare recenzii, note de a verifica topuri in functie de anumite criterii.

Clasa de baza ObiectMuzical cu clasele derivate: Melodie, Album, Artist
Functia virtuala in ObiectMuzical afiseazaDetalii(), suprascrisa in cele 3 clase derivate
Clone in ObiectMuzical std::shared_ptr<ObiectMuzical> clone() const = 0;
Folosire shared_ptr si dynamic_cast
Exceptii MuzicaException, NotaInvalidaException, FisierInvalidException
