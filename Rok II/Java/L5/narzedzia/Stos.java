package narzedzia;
/**
 * Klasa implementująca stos zbudowany na bazie klasy Lista
 *
 */
public class Stos<T> {

    Lista<T> stos;

    public Stos(){
        stos = new Lista<T>();
    }

    public void wloz(T war) throws ListaWyjatek{
        stos.DodajKoniec(war);
    }

    public T wyciagnij() throws ListaWyjatek{
        T przekaz = stos.Ostatni();
        stos.usunKoniec();
        return przekaz;
    }

    public void usun() throws ListaWyjatek{
        stos.usunPoczatek();
    }

    public int size(){
        return stos.size();
    }

    public boolean isEmpty(){
        return stos.isEmpty();
    }
}
