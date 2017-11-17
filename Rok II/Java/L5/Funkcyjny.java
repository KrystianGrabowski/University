package onp;
import wyjatki.WyjatkiONP;
import wyjatki.ONP_BladArgumentu;
/**
 * Interfejs Funkcyjny dziedziczy po interfejsie Obliczalny
 * Wprowadza dla funkcji możliwość sprawdzenia ich arnosci,
 * brakujacych argumentów oraz możliwość dodania elementu
 */

public interface Funkcyjny extends Obliczalny{
    /**
     * Podaje arność funkcji czyli jej liczbę argumentów
     * @return liczba typu int
     */
    int arnosc();

    /**
     * Podaje ile argumentów należy jeszcze podac
     * @return liczba typu int
     */
    int brakujaceArgumenty();

    /**
     * Podaje ile argumentów należy jeszcze podac
     * @param arugment
     */
    void dodajArgument(double argument) throws WyjatkiONP;
}
