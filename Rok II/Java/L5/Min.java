package onp;

/**
 * Minimum ONP
 */
public class Min extends Op2Arg{

    @Override
    public double obliczWartosc(){
        return Math.min(argument1, argument2);
    }

    @Override
    public String toString(){
        return "min";
    }
}
