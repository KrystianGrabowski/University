import narzedzia.Lista;
import narzedzia.Para;
import narzedzia.ListaWyjatek;

public class Main{
    public static void main(String[] args){
        try{
            Lista<Para <String, Double> > zmienne = new Lista<Para <String, Double> >();
            Para p1 = new Para("x",10);
            zmienne.DodajKoniec(p1);
            Para p2 = new Para("y",10);
            zmienne.DodajKoniec(p2);
            Wyrazenie w = new Wyrazenie("2 3 +",zmienne);
        }
        catch (ListaWyjatek e){
            System.out.println(e);

        }



    }

}
