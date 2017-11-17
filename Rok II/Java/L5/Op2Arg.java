package onp;
import wyjatki.WyjatkiONP;
import wyjatki.ONP_BladArgumentu;

/**
 * Klasa nadrzędna dla funkcji dwuargumentowych
 */
public abstract class Op2Arg extends Funkcja{

    protected double argument1;
    protected double argument2;
    public int stan_arg = 0;


    public Op2Arg(){}

    public Op2Arg(double argument1, double argument2){
        this.argument1 = argument1;
        this.argument2 = argument2;
        stan_arg = 2;
    }

    @Override
    public int arnosc(){
        return 1;
    }

    @Override
    public int brakujaceArgumenty(){
        return 2 - stan_arg;
    }

    @Override
    public void dodajArgument(double argument) throws WyjatkiONP{
        if (stan_arg == 2){
            throw new ONP_BladArgumentu("Podano za duzo argumentow do funkcji");
        }
        else{
            if (stan_arg == 0){
                this.argument1 = argument1;
                stan_arg ++;
            }
            else if (stan_arg == 1){
                this.argument2 = argument2;
                stan_arg ++;
            }

        }
        }

}
