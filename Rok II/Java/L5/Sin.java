
/**
 * Sinus ONP
 */
public class Sin extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.sin(argument);
    }

    @Override
    public String toString(){
        return "sin";
    }
}
