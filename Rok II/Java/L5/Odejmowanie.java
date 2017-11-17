package onp;

/**
 * Odejmowanie ONP
 */
public class Odejmowanie extends Op2Arg{

    @Override
    public double obliczWartosc(){
        return argument1 - argument2;
    }

    @Override
    public String toString(){
        return "-";
    }
}
