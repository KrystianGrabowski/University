import narzedzia.Para;
import wyjatki.WyjatkiONP;
import wyjatki.ONP_BladArgumentu;

/**
 * Klasa Zmienna przetrzymuje parę klucz-wartość (String-double) 
 *
 */

public class Zmienna extends Operand implements Obliczalny{
    public final String id;
    private double wartosc;
    private final String wzor = "\\p{Alpha}\\p{Alnum}*";

    public Zmienna(String id, double wartosc) throws WyjatkiONP{
        if (!id.matches(wzor)){
            throw new ONP_BladArgumentu("Identyfikator zmiennej nie pasuje do wzroca");
        }
        this.id = id;
        this.wartosc = wartosc;

    }

    @Override
    public double obliczWartosc(){
        return wartosc;
    }

    public String toString(){
        return id;
    }
}
