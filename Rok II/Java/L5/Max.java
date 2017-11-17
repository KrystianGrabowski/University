package onp;

/**
 * Maximum ONP
 */
public class Max extends Op2Arg{

    @Override
    public double obliczWartosc(){
        return Math.max(argument1, argument2);
    }

    @Override
    public String toString(){
        return "max";
    }
}
