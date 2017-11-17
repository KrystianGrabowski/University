package onp;

/**
 * Logarytm naturalny ONP
 */
public class Ln extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.log(argument);
    }

    @Override
    public String toString(){
        return "ln";
    }
}
