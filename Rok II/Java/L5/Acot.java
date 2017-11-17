package onp;

public class Acot extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.PI/2 - Math.atan(argument);
    }

    @Override
    public String toString(){
        return "acot";
    }
}
