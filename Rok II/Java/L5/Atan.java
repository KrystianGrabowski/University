package onp;

/**
 * Arcus tangens ONP
 */
public class Atan extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.atan(argument);
    }

    @Override
    public String toString(){
        return "atan";
    }
}
