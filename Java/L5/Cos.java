
/**
 * Cosinus ONP
 */
public class Cos extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.cos(argument);
    }

    @Override
    public String toString(){
        return "cos";
    }
}
