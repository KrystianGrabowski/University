package onp;

/**
 * Sufit ONP
 */
public class Ceil extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.ceil(argument);
    }

    @Override
    public String toString(){
        return "ceil";
    }
}
