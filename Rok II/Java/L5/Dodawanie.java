
/**
 * Dodawanie ONP
 */
public class Dodawanie extends Op2Arg{

    @Override
    public double obliczWartosc(){
        return argument1 + argument2;
    }

    @Override
    public String toString(){
        return "+";
    }
}
