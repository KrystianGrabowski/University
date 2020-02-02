import wyjatki.WyjatkiONP;
import wyjatki.ONP_BladArgumentu;

/**
 * Klasa nadrzędna dla funkcji jednoagumentowych
 */
public abstract class Op1Arg extends Funkcja{

    protected double argument;
    public int stan_arg = 0;


    public Op1Arg(){}

    public Op1Arg(double argument){
        this.argument = argument;
        stan_arg++;
    }

    @Override
    public int arnosc(){
        return 1;
    }

    @Override
    public int brakujaceArgumenty(){
        return (1 - stan_arg);
    }

    @Override
    public void dodajArgument(double argument) throws WyjatkiONP{
        if (stan_arg == 1){
            throw new ONP_BladArgumentu("Podano za duzo argumentow do funkcji");
        }
        else{
            this.argument = argument;
            stan_arg ++;
        }
        }

}
