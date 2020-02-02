package narzedzia;
/**
 * Klasa implementująca stos zbudowany na bazie klasy Lista
 *
 */
public class Stos<T> {

    Lista<T> stos;

    /**
     * Inincjowanie stosu nie posiadającego żadnego elementu
     */
    public Stos(){
        stos = new Lista<T>();
    }

    /**
     * Dodaje element na wierzchołek stosu
     * @param war wartość do dodania
     */
    public void wloz(T war) throws ListaWyjatek{
        stos.DodajKoniec(war);
    }

    /**
     * Zwraca warość elementu z wierzchołka stosu oraz usuwa go
     * @return element z wirzchołka stosu
     */
    public T wyciagnij() throws ListaWyjatek{
        T przekaz = stos.Ostatni();
        stos.usunKoniec();
        return przekaz;
    }

    /**
     * Usuwa element z wierzchołka stosu
     */
    public void usun() throws ListaWyjatek{
        stos.usunKoniec();
    }

    public int size(){
        return stos.size();
    }

    public boolean isEmpty(){
        return stos.isEmpty();
    }

}
