package onp;

/**
 * Część ułamkowa ONP
 */
public class Frac extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return argument - Math.floor(argument);
    }

    @Override
    public String toString(){
        return "frac";
    }
}
