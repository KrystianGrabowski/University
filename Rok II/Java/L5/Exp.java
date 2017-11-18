
/**
 * Exp ONP
 */
public class Exp extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.exp(argument);
    }

    @Override
    public String toString(){
        return "exp";
    }
}
