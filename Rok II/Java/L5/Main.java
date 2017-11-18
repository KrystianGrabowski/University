import narzedzia.Lista;
import narzedzia.Para;
import narzedzia.ListaWyjatek;
import wyjatki.*;
import narzedzia.*;
import java.util.Scanner;


public class Main{
    public static void main(String[] args){
        try{
            Lista<Para> zmienne = new Lista<Para>();
            Para p1 = new Para("x",5);
            zmienne.DodajKoniec(p1);
            Para p2 = new Para("y",2);
            zmienne.DodajKoniec(p2);

        }
        catch(ListaWyjatek e){
            System.err.println(e);
        }
        Lista<Para> zmienne = new Lista<Para>();
        String wyrazenie ="";
        String[] tab;
            while (true){
                try{


                Scanner input = new Scanner(System.in);
                String tekst = input.nextLine();
                tab = tekst.split(" ");
                if (tab[0].equals("calc")){
                    for (int i = 1; i < tab.length; i++){
                        wyrazenie += tab[i];
                        if (i != tab.length-1){
                            wyrazenie += " ";
                        }
                    }
                    Wyrazenie w = new Wyrazenie(wyrazenie,zmienne);
                    System.out.println(w.obliczONP());
                    wyrazenie = "";
                }
                else if (tab[0].equals("exit")){
                    break;
                }
                else{
                    throw new AssertionError("Nieznana komenda");
                }
            }
        catch (WyjatkiONP e){
            System.err.println(e);
        }
        catch (AssertionError e){
            System.err.println(e);
        }
    }
}
}
