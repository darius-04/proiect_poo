Mini aplicatie de genul RateYourMusic, bazata pe publicarea de note si recenzii unor anumite obiecte muzicale, precum recenzii sau note.
Clasa principala ObiectMuzical are mostenirile Artist, Melodie si Album, si contine o functie virtuala de afisare a anumitor detalii despre fiecare obiect.
Exista posibilitatea de adaugare recenzii, note de a verifica topuri in functie de anumite criterii.

Clasa de baza ObiectMuzical cu clasele derivate: Melodie, Album, Artist
Functia virtuala in ObiectMuzical afiseazaDetalii(), suprascrisa in cele 3 clase derivate
Clone in ObiectMuzical std::shared_ptr<ObiectMuzical> clone() const = 0;
Folosire shared_ptr si dynamic_cast
Exceptii MuzicaException, NotaInvalidaException, FisierInvalidException

Utilizarea template in clasa Recenzie ce ofera flexibilitate tipului nota( int, double, float) si in clasa SortStrategy pentru a oferi posibilitatea sortarii a tuturor mostenirilor de tip ObiectMuzical( Artist, Album, Melodie).

Design patternurile folosite sunt Factory pentru crearea mai generica o obiectelor muzicale si Strategy, implementand o strategie de sortare pe mai multe criterii (alfabetica, dupa nota, dupa numarul de melodii) pentru a generaliza si a facilita crearea unor topuri.

Factory-ul este utilizat in main pentru a crea obiecte de tipul Melodie si Recenzie. Strategiile de sortare sunt utilizate in cadrul clasei Topuri pentru realizarea a ierarhiilor de melodii, artisti sau albume si in clasa Artist pentru a sorta albumele unui artist in functie de nota.
