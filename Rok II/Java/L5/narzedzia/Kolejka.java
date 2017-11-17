package narzedzia;

/**
 * Klasa implementująca kolejkę zbudowana na bazie klasy Lista
 *
 */
public class Kolejka<T> {

    Lista<T> kolejka;

    /**
     * Inincjowanie kolejki nie posiadającej żadnego elementu
     */

    public Kolejka(){
        kolejka = new Lista<T>();
    }

    /**
     * Dodaje element na koniec kolejki
     * @param war wartość do dodania na koniec kolejki
     */
    public void wloz(T war) throws ListaWyjatek{
        kolejka.DodajKoniec(war);
    }

    /**
     * Zwraca warość elementu z poczatki kolejki oraz usuwa go
     * @return wartość pierwszego elemntu z kolejki
     */
    public T wyciagnij() throws ListaWyjatek{
        T przekaz = kolejka.Pierwszy();
        kolejka.usunPoczatek();
        return przekaz;
    }

    /**
     * Usuwa element z początku kolejki
     */
    public void usun() throws ListaWyjatek{
        kolejka.usunPoczatek();
    }

    public int size(){
        return kolejka.size();
    }

    public boolean isEmpty(){
        return kolejka.isEmpty();
    }
}
