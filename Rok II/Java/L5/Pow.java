package onp;

public class Pow extends Op2Arg{

    @Override
    public double obliczWartosc(){
        return Math.pow(argument1, argument2);
    }

    @Override
    public String toString(){
        return "pow";
    }
}
