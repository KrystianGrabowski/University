package onp;

public class Dzielenie extends Op2Arg{

    @Override
    public double obliczWartosc(){
        if (argument2 != 0){
            return argument1 / argument2;
        }
        return 0;
    }

    @Override
    public String toString(){
        return "/";
    }
}
