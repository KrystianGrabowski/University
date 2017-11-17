package onp;

public class Pi extends Op0Arg{

    @Override
    public double obliczWartosc(){
        return(Math.PI);
    }

    @Override
    public String toString(){
        return "PI";
    }
}
