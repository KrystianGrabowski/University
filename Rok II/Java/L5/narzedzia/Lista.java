package narzedzia;


/**
 * Klasa generyczna implementująca listę dwukierunkową
 * posiada dwa obiekty typu Wezel jeden służy za początek drugi za koniec naszj listy
 */

public class Lista<T> {
    Wezel poczatek;
    Wezel koniec;
    private int rozmiar;

    /**
     * Inincjowanie listy nie posiadającej żadnego elementu
     * jedynie węzły oznaczające koniec i początek.
     */

    public Lista(){
        poczatek = new Wezel();
        koniec = new Wezel();
        poczatek.poprzedni = poczatek;
        poczatek.nastepny = koniec;
        koniec.poprzedni = poczatek;
        koniec.nastepny = koniec;
        rozmiar = 0;
    }
    /**
     * Dodaje element na koniec listy
     * @param war wartość do dodania na koniec listy
     * @throws ListaWyjatek kiedy podany agument jest nullem
     */
    public void DodajKoniec(T war) throws ListaWyjatek{
        if (war == null){
            throw new ListaProblemNull("argument ma wartosc null");
        }
        Wezel Nowy = new Wezel();
        Nowy.wartosc = war;
        rozmiar++;
        Nowy.poprzedni = koniec.poprzedni;
        Nowy.nastepny = koniec;
        koniec.poprzedni.nastepny = Nowy;
        koniec.poprzedni = Nowy;
    }

    /**
     * Dodaje element na poczętek listy
     * @param war wartość do dodania na początek listy
     * @throws ListaWyjatek kiedy podany agument jest nullem
     */
    public void DodajPoczatek(T war) throws ListaWyjatek{
        if (war == null){
            throw new ListaProblemNull("argument ma wartosc null");
        }
        Wezel Nowy = new Wezel();
        Nowy.wartosc = war;
        rozmiar++;
        Nowy.poprzedni = poczatek;
        Nowy.nastepny = poczatek.nastepny;
        poczatek.nastepny.poprzedni = Nowy;
        poczatek.nastepny = Nowy;

    }

    public int size(){
        return rozmiar;
    }


    public boolean isEmpty(){
        return (rozmiar == 0);
    }

    /**
     * Wymazuje wszystkie dane z listy
     */
    public void czysc(){
        poczatek.nastepny = koniec;
        koniec.poprzedni = poczatek;
        rozmiar = 0;
    }

    /**
     * Usuwa ostatni element z listy
     * @throws ListaWyjatek kiedy lista jest pusta
     */
    public void usunKoniec() throws ListaWyjatek{
        if (this.isEmpty()){
            throw new ListaPusta("Lista jest pusta");
        }
        koniec.poprzedni = koniec.poprzedni.poprzedni;
        koniec.poprzedni.poprzedni.nastepny = koniec;
        rozmiar--;
    }

    /**
     * Usuwa pierwszy element z listy
     * @throws ListaWyjatek kiedy lista jest pusta
     */
    public void usunPoczatek() throws ListaWyjatek{
        if (this.isEmpty()){
            throw new ListaPusta("Lista jest pusta");
        }
        poczatek.nastepny = poczatek.nastepny.nastepny;
        poczatek.nastepny.nastepny.poprzedni = poczatek;
        rozmiar--;
    }


    /**
     * Ususwa podany element z listy
     * @param war klucz mówiący co należy usunąć
     * @throws ListaWyjatek kiedy agument jest nullem, lista pusta lub brak elementu
     */
    public void usun(T war) throws ListaWyjatek{
        if (war == null){
            throw new ListaProblemNull("argument ma wartosc null");
        }
        if (this.isEmpty()){
            throw new ListaPusta("Lista jest pusta");
        }
        if (this.szukaj(war) == null){
            throw new ListaNieistniejacyElement("Nie można znaleźć elementu w liscie");
        }
        Wezel Obecny = poczatek.nastepny;
        while(Obecny != koniec){
            if (Obecny.wartosc.equals(war)){
                Obecny.poprzedni.nastepny = Obecny.nastepny;
                Obecny.nastepny.poprzedni = Obecny.poprzedni;
                rozmiar--;
            }
            Obecny = Obecny.nastepny;
        }
    }

    /**
     * Zwraca wartosc pierwszego elementu listy
     * @throws ListaWyjatek kiedy lista jest pusta
     * @return wartosc pierwszego elementu listy
     */
    public T Pierwszy() throws ListaWyjatek{
        if (this.isEmpty()){
            throw new ListaPusta("Lista jest pusta");
        }
        return poczatek.nastepny.wartosc;
    }

    /**
     * Zwraca wartosc ostatniego elementu listy
     * @throws ListaWyjatek kiedy lista jest pusta
     * @return wartosc ostatniego elementu listy
     */
    public T Ostatni() throws ListaWyjatek{
        if (this.isEmpty()){
            throw new ListaPusta("Lista jest pusta");
        }
        return koniec.poprzedni.wartosc;
    }

    /**
     * Wyszukuje w całej liście wartości i zwraca ją
     * @param war klucz mówiący co należy wyszukać
     * @return wartość lub null
     * @throws ListaWyjatek kiedy argument ma wartość null, lub wartosc węzła równa jest null
     */
    public T szukaj(T war) throws ListaWyjatek{
        if (war == null){
            throw new ListaProblemNull("argument ma wartosc null");
        }
        Wezel Obecny = poczatek.nastepny;
        while (Obecny != koniec){
            if (Obecny.wartosc.equals(war)){
                if (Obecny.wartosc == null){
                    throw new ListaProblemNull("funckcja szukaj zwraca null pomimo istnienia elwmwntu w tablicy");
                }
                return Obecny.wartosc;
            }
            Obecny = Obecny.nastepny;
        }
        return null;
    }

    public String toString(){
        Wezel Obecny = poczatek.nastepny;
        while (Obecny != koniec){
            System.out.println(Obecny.wartosc);
            Obecny = Obecny.nastepny;


        }
    return "AAA";
    }








    /**
     * Klasa wewnętrzna klasy Lista przechowywująca dwa wskaźniki oraz pewną wartość
     *
     */
    private class Wezel{
        public Wezel nastepny;
        public Wezel poprzedni;
        public T wartosc;

        public Wezel(){
            nastepny = null;
            poprzedni = null;
            wartosc = null;
        }
    }
}
