package onp;
import wyjatki.WyjatkiONP;
import wyjatki.ONP_BladArgumentu;

/**
 * Klasa nadrzędna dla funkcji zeroagumentowych
 */

public abstract class Op0Arg extends Funkcja{

    public Op0Arg(){}

    @Override
    public int arnosc(){
        return 0;
    }

    @Override
    public int brakujaceArgumenty(){
        return 0;
    }

    @Override
    public void dodajArgument(double argument) throws WyjatkiONP{
        throw new ONP_BladArgumentu("Podano za duzo argumentow do funkcji");
    }
}
