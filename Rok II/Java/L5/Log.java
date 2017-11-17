package onp;

/**
 * Logarytm ONP
 */
public class Log extends Op2Arg{

    @Override
    public double obliczWartosc(){
        return Math.max(argument1, argument2);
    }

    @Override
    public String toString(){
        return "log";
    }
}
