
/**
 * Wartosć bezwzgledna ONP
 */
public class Abs extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.abs(argument);
    }

    @Override
    public String toString(){
        return "abs";
    }
}
