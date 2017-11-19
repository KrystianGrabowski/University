import narzedzia.Kolejka;
import narzedzia.Stos;
import narzedzia.Lista;
import narzedzia.Para;
import java.util.regex.Pattern;
import wyjatki.*;
import narzedzia.ListaWyjatek;

/**
 * Klasa Wyraznie której głównym zadaniem jest poprawnie obliczyc wyrażenie w ONP
 *
 **/

public class Wyrazenie{
    private Kolejka kolejka;
    private Stos stos;
    private Lista zmienne;

    public Wyrazenie (String onp, Lista zm){
        kolejka = new Kolejka<Double>();
        stos = new Stos<Double>();
        zmienne = zm;

        String[] elementy = onp.split(" ");
        try{
            nakolejke(elementy);
        }
        catch (WyjatkiONP e) {

        }


    }

    private void nakolejke(String[] elementy) throws WyjatkiONP{
        try{
            for (String element : elementy) {
                if(Pattern.matches("(?i)acot", element)) kolejka.wloz(new Acot());
                else if(Pattern.matches("(?i)abs", element))kolejka.wloz(new Abs());
                else if(Pattern.matches("(?i)floor", element))kolejka.wloz(new Floor());
                else if(Pattern.matches("(?i)sgn", element))kolejka.wloz(new Sgn());
                else if(Pattern.matches("(?i)pow", element))kolejka.wloz(new Pow());
                else if(Pattern.matches("(?i)max", element))kolejka.wloz(new Max());
                else if(Pattern.matches("(?i)min", element))kolejka.wloz(new Min());
                else if(Pattern.matches("(?i)log", element))kolejka.wloz(new Log());
                else if(Pattern.matches("\\*", element))kolejka.wloz(new Mnozenie());
                else if(Pattern.matches("\\/", element))kolejka.wloz(new Dzielenie());
                else if(Pattern.matches("\\-", element))kolejka.wloz(new Odejmowanie());
                else if(Pattern.matches("\\+", element))kolejka.wloz(new Dodawanie());
                else if(Pattern.matches("(?i)ceil", element))kolejka.wloz(new Ceil());
                else if(Pattern.matches("(?i)frac", element))kolejka.wloz(new Frac());
                else if(Pattern.matches("(?i)sin", element))kolejka.wloz(new Sin());
                else if(Pattern.matches("(?i)cos", element))kolejka.wloz(new Cos());
                else if(Pattern.matches("(?i)atan", element))kolejka.wloz(new Atan());
                else if(Pattern.matches("(?i)ln", element))kolejka.wloz(new Ln());
                else if(Pattern.matches("(?i)exp", element))kolejka.wloz(new Exp());
                else if(Pattern.matches("(?i)pi", element))kolejka.wloz(new Pi());
                else if(Pattern.matches("(?i)e", element))kolejka.wloz(new E());
                else if(Pattern.matches("[+-]?[0-9]+(\\.[0-9]+)?", element)){
                    kolejka.wloz(new Liczba(Double.parseDouble(element)));
                }
                else {
                    if (zmienne.szukaj(element) == null){
                        throw new ONP_NieznanySymbol("Nie rozpoznano symbolu");
                    }
                    else{
                        Object o = zmienne.szukaj(element);
                        if (o instanceof Para){
                            Para p = (Para) o;
                            double z = p.getValue();
                            kolejka.wloz(new Zmienna(element,z));

                        }
                    }
                }
            }
        }
        catch (ListaWyjatek e){
            System.err.println(e);
        }
    }

    /**
     * Oblicza wyrazenie w Onp
     * @return wartość wyrażenie typ double
     * @throws WyjatkiONP kiedy pojawi się bład w zapisie ONP 
     */
    public double obliczONP() throws WyjatkiONP{
        try{
            Object o;
            while(kolejka.size() != 0){
                o = kolejka.wyciagnij();
                if (o instanceof Funkcja){
                    Funkcja f = (Funkcja) o;
                    if (stos.size() < f.arnosc()) {throw new ONP_BladArgumentu("Za mało argumentów");}
                    while(f.brakujaceArgumenty() > 0){
                            Object obj = stos.wyciagnij();
                            if (obj instanceof Double){
                                Double d = (Double) obj;
                                f.dodajArgument(d);
                            }
                    }
                    stos.wloz(f.obliczWartosc());

                }
                else if (o instanceof Operand){
                    Operand op = (Operand) o;
                    stos.wloz(op.obliczWartosc());

                }
            }
            if (stos.size() != 1){
                throw new WyjatkiONP("Po obliczeniu w stosie jest wiecej niz jeden wynik");
            }
            Object object = stos.wyciagnij();
            Double d = (Double) object;
            return d;
        }
        catch (ListaWyjatek e){
            System.err.println(e);
        }
        return 0;

    }




}
