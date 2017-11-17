package onp;

public class Sgn extends Op1Arg{

    @Override
    public double obliczWartosc(){
        return Math.signum(argument);
    }

    @Override
    public String toString(){
        return "sgn";
    }
}
