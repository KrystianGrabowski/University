import wyjatki.*;
/**
 * Interejs Obliczalny
 *
 */

public interface Obliczalny{

    /**
     * metoda zwracjaca wartosc wyrazenia zapisanego w ONP
     * @return wynik typu dobule
     * @throws WyjatkiONP gdy nie można z jakiegoś powodu obliczyc wartosci
     */
    double obliczWartosc() throws WyjatkiONP;
}
