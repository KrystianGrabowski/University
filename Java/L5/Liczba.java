
public class Liczba extends Operand implements Obliczalny{

    double wartosc;

    public Liczba(double wartosc){
        this.wartosc = wartosc;
    }

    @Override
    public double obliczWartosc(){
        return wartosc;
    }

    @Override
    public String toString(){
        return String.valueOf(wartosc);
    }
}
