
/**
 * Podłoga ONP
 */
public class Floor extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.floor(argument);
    }

    @Override
    public String toString(){
        return "floor";
    }
}
