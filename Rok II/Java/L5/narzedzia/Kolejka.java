package narzedzia;

/**
 * Klasa implementująca kolejkę zbudowana na bazie klasy Lista
 *
 */
public class Kolejka<T> {

    Lista<T> kolejka;

    public Kolejka(){
        kolejka = new Lista<T>();
    }

    public void wloz(T war) throws ListaWyjatek{
        kolejka.DodajKoniec(war);
    }

    public T wyciagnij() throws ListaWyjatek{
        T przekaz = kolejka.Pierwszy();
        kolejka.usunPoczatek();
        return przekaz;
    }

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
