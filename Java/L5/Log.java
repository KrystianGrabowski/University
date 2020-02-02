import wyjatki.*;;
/**
 * Logarytm ONP
 */
public class Log extends Op2Arg{

    @Override
    public double obliczWartosc() throws WyjatkiONP{
        if (argument1 < 1 || argument2 < 0 ){
            throw new ONP_BladArgumentu("argumenty do logarytmu niepoprawne");
        }
        return Math.log(argument1) / Math.log(argument2);
    }

    @Override
    public String toString(){
        return "log";
    }
}
