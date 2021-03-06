import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.io.File;
import java.io.Serializable;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;



public class Klienci extends JFrame implements Serializable, ActionListener {
	
	private static final long serialVersionUID = 1L;
	public ArrayList <Klient> klienci = new ArrayList <Klient>();
	public JTextField PImie, PNazwisko, PZakup, PWaznosc, PWiek, PPesel;
	public JLabel W;
	public JButton Spr, Kup ,Z, Wroc, Rej, Wrocr, POTW;
	public JComboBox boks;
	public JFrame framen, frame, framer;
	public String rodzaj;
	Map<Integer, Integer> map = new HashMap<Integer, Integer>();

	public Klienci(String zapisK){
		map.put(1, 31);
		map.put(2, 28);
		map.put(3, 31);
		map.put(4, 30);
		map.put(5, 31);
		map.put(6, 30);
		map.put(7, 31);
		map.put(8, 31);
		map.put(9, 30);
		map.put(10, 31);
		map.put(11, 30);
		map.put(12, 31);
		rodzaj = zapisK;
	}
	
	public void dodaj(String imie, String nazwisko, String datax, String datay, int wiek, String pesel)
	{
		Klient K = new Klient(imie,nazwisko,datax,datay,wiek,pesel);
		klienci.add(K);
	}
	public boolean klient(String imie, String nazwisko)
	{
		for (int i=0; i<klienci.size(); i++)
		{
			if (Objects.equals((klienci.get(i).imie), imie))
			{
				if (Objects.equals((klienci.get(i).nazwisko), nazwisko))
				{
					return true;
				}
			}
		}

		return false;
	}
	
	public void usun(String imie, String nazwisko)
	{
		if (klient(imie,nazwisko) == true)
		{
			for (int i=0; i<klienci.size(); i++)
			{
				if (Objects.equals((klienci.get(i).imie), imie))
				{
					if (Objects.equals((klienci.get(i).nazwisko), nazwisko))
					{
						klienci.remove(i);
					}
				}
			}
		}
		else
		{
			System.out.println("Nie znaleziono klienta " + imie + " " + nazwisko);
		}
	}
	
	public Klient GT(String imie, String nazwisko){
		if (klient(imie,nazwisko) == true)
		{
			for (int i=0; i<klienci.size(); i++)
			{
				if (Objects.equals((klienci.get(i).imie), imie))
				{
					if (Objects.equals((klienci.get(i).nazwisko), nazwisko))
					{
						return klienci.get(i);
					}
				}
			}
		}
		else
		{
			System.out.println("Nie znaleziono klienta " + imie + " " + nazwisko);
		}
		return null;
	}
	
	public Integer ile_dni_wazny(String imie, String nazwisko){
        String obecnaData;
        DateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        java.util.Date date1 = new java.util.Date();
        obecnaData = format.format(date1);
        DataK ob = new DataK(obecnaData);
        Integer r = ob._rok();
        Integer m = ob._miesiac();
        Integer d = ob._dzien();
        Klient k = GT(imie,nazwisko);
        Integer ILOSC = 0;
        if (k != null){
        	DataK x = k.KarnetK();
        	if (x._rok() < r){
        		return 0;
        	}
        	else{
        		ILOSC = ILOSC + 365 * (x._rok() - r);
        	}
        	if (x._miesiac() > m){
        		Integer a = x._miesiac();
        		while(m != a){
        			ILOSC = ILOSC + (map.get(m));
        			m = m + 1;
        		}
        	}
        	ILOSC = ILOSC + (x._dzien() - d);
            return ILOSC;
        	}

        else{
        	System.out.print("Brak klienta w bazie");
        }
        return null;
	}
	
	public void przedluz(String imie, String nazwisko, Integer dni){
		Klient k = GT(imie, nazwisko);
		if (k!= null){
        	DataK x = k.KarnetK();
        	Integer d = x._dzien();
        	Integer m = x._miesiac();
        	Integer r = x._rok();
        	d = d + dni;
        	while (d > map.get(m)){
        		d = d - map.get(m);
        		m = m + 1;
        		if (m > 12){
        			m = 1;
        			r = r+ 1;
        		}
        	}
        	DataK nw = new DataK(r,m,d);
        	k.DY = nw;
		}
	}
	
	public String ToStringK(){
		String lista = "";
		for (int i=0; i<klienci.size(); i++)
		{
			Klient k = klienci.get(i);
			DataK x = k.KarnetP();
			String xa = x._rok() + "-" + x._miesiac() + "-" + x._dzien();
			DataK y = k.KarnetK();
			String ya = y._rok() + "-" + y._miesiac() + "-" + y._dzien();
			lista = lista + k.imie + " " + k.nazwisko + " " + xa + " " + ya + " " + k.wiek + " " + k.pesel ;
			lista = lista + "\n";
		}
		return lista;
		
	}
	public void WriteToFile(String nazwa) throws FileNotFoundException{
		PrintWriter zapis = new PrintWriter(nazwa);
		String lklienci = ToStringK();
		zapis.print(lklienci);
		zapis.close();
	}
	public void ReadFromFile(String nazwa) throws FileNotFoundException{
		File plik = new File(nazwa);
		Scanner odczyt = new Scanner(plik);

		while(odczyt.hasNext())
		{
			String linia = odczyt.nextLine();
			String T[] = linia.split(" ");
			int wiek = Integer.valueOf(T[4]);
			dodaj(T[0],T[1],T[2],T[3],wiek,T[5]);
		}
		odczyt.close();
	}
	
	public void Edycja()
	{
		framen = new JFrame();
      
        setTitle("Karnet");
        JPanel panel = new JPanel();
        panel.setLayout(null);
        panel.setBackground(Color.black);
        framen.add(panel);
        
		JLabel imie_etykieta = new JLabel("Imie");
        imie_etykieta.setForeground(Color.white);
		imie_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		imie_etykieta.setBounds(30,30,60,20);
		panel.add(imie_etykieta);
		PImie = new JTextField(0);
		PImie.setBounds(100, 30, 130, 30);
		panel.add(PImie);
		
		JLabel nazwisko_etykieta = new JLabel("Nazwisko");
        nazwisko_etykieta.setForeground(Color.white);
		nazwisko_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		panel.add(nazwisko_etykieta);
		nazwisko_etykieta.setBounds(30,80,80,30);
		PNazwisko = new JTextField(40);
		PNazwisko.setBounds(100,80,130,30);
		panel.add(PNazwisko);
		
		
		Spr = new JButton("Sprawdz");
        Spr.setBackground(new Color(203,137,247));
		Spr.setBounds(300,10,120,70);
		Spr.addActionListener(this);
		panel.add(Spr);
		
		Kup = new JButton("Kup");
        Kup.setBackground(new Color(203,137,247));
		Kup.setBounds(300,80,120,70);
		Kup.addActionListener(this);
		panel.add(Kup);
		
		W = new JLabel();
		W.setFont(new Font("Serif", Font.PLAIN, 30));
		W.setLocation(40, 150);
		W.setSize(500, 50);
		panel.add(W);

		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        framen.setSize(500, 300);
        framen.setVisible(true);
	}
	public void kupowanie(){
		
		frame = new JFrame();
	      
        setTitle("Karnet");
        JPanel panel = new JPanel();
        panel.setLayout(null);
        panel.setBackground(Color.black);
        frame.add(panel);
        
		JLabel imie_etykieta = new JLabel("Imie");
		imie_etykieta.setForeground(Color.white);
		imie_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		imie_etykieta.setBounds(30,30,60,20);
		panel.add(imie_etykieta);
		PImie = new JTextField(0);
		PImie.setBounds(100, 30, 130, 30);
		panel.add(PImie);
		
		JLabel nazwisko_etykieta = new JLabel("Nazwisko");
		nazwisko_etykieta.setForeground(Color.white);
		nazwisko_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		panel.add(nazwisko_etykieta);
		nazwisko_etykieta.setBounds(30,80,80,30);
		PNazwisko = new JTextField(40);
		PNazwisko.setBounds(100,80,130,30);
		panel.add(PNazwisko);
		
		JLabel ilosc_etykieta = new JLabel("Ilosc dni");
		ilosc_etykieta.setForeground(Color.white);
		ilosc_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		ilosc_etykieta.setBounds(30,130,80,30);
		panel.add(ilosc_etykieta);
		boks = new JComboBox();
		boks.setBounds(100,130,100,20);
		boks.addItem("30");
		boks.addItem("90");
		boks.addItem("120");
		boks.addItem("240");
		boks.addItem("360");
		panel.add(boks);
		boks.addActionListener(this);
		
		Z = new JButton("Kup");
        Z.setBackground(new Color(203,137,247));
		Z.setBounds(300,100,120,70);
		Z.addActionListener(this);
		panel.add(Z);

		Wroc = new JButton("<-");
        Wroc.setBackground(new Color(203,137,247));
		Wroc.setBounds(430,0,50,30);
		Wroc.addActionListener(this);
		panel.add(Wroc);
		
		Rej = new JButton("Rejstracja");
        Rej.setBackground(new Color(203,137,247));
		Rej.setBounds(380,40,100,30);
		Rej.addActionListener(this);
		panel.add(Rej);

		
		W = new JLabel();
		W.setFont(new Font("Serif", Font.PLAIN, 30));
		W.setLocation(40, 170);
		W.setSize(500, 50);
		panel.add(W);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setSize(500, 300);
        frame.setVisible(true);
	}
	public void rej(){
		framer = new JFrame();
	      
        setTitle("Karnet");
        JPanel panel = new JPanel();
        panel.setLayout(null);
        panel.setBackground(Color.black);
        framer.add(panel);
        
		JLabel imie_etykieta = new JLabel("Imie");
		imie_etykieta.setForeground(Color.white);
		imie_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		imie_etykieta.setBounds(30,10,60,20);
		panel.add(imie_etykieta);
		PImie = new JTextField(0);
		PImie.setBounds(100, 10, 130, 30);
		panel.add(PImie);
		
		JLabel nazwisko_etykieta = new JLabel("Nazwisko");
		nazwisko_etykieta.setForeground(Color.white);
		nazwisko_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		panel.add(nazwisko_etykieta);
		nazwisko_etykieta.setBounds(30,50,80,30);
		PNazwisko = new JTextField(40);
		PNazwisko.setBounds(100,50,130,30);
		panel.add(PNazwisko);
		
		JLabel wiek_etykieta = new JLabel("Wiek");
		wiek_etykieta.setForeground(Color.white);
		wiek_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		panel.add(wiek_etykieta);
		wiek_etykieta.setBounds(30,90,80,30);
		PWiek = new JTextField(40);
		PWiek.setBounds(100,90,130,30);
		panel.add(PWiek);
		
		JLabel pesel_etykieta = new JLabel("Pesel");
		pesel_etykieta.setForeground(Color.white);
		pesel_etykieta.setFont(new Font("Serif", Font.PLAIN, 16));
		panel.add(pesel_etykieta);
		pesel_etykieta.setBounds(30,130,80,30);
		PPesel = new JTextField(40);
		PPesel.setBounds(100,130,130,30);
		panel.add(PPesel);

		POTW = new JButton("Rejestruj");
        POTW.setBackground(new Color(203,137,247));
		POTW.setBounds(350,150,100,50);
		POTW.addActionListener(this);
		panel.add(POTW);

		Wrocr = new JButton("<-");
        Wrocr.setBackground(new Color(203,137,247));
		Wrocr.setBounds(430,0,50,30);
		Wrocr.addActionListener(this);
		panel.add(Wrocr);

		
		W = new JLabel();
		W.setFont(new Font("Serif", Font.PLAIN, 30));
		W.setLocation(40, 170);
		W.setSize(500, 50);
		panel.add(W);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        framer.setSize(500, 300);
        framer.setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		String d;
		if (e.getSource() == Spr)
		{
			if (ile_dni_wazny(PImie.getText(),PNazwisko.getText()) == null)
			{
				d = "Brak klienta w bazie";	
			}
			else
			{
				d = " Karnet wazny przez : " + String.valueOf(ile_dni_wazny(PImie.getText(),PNazwisko.getText())) + " dni";
			}
			
			W.setText(d);
		}
		if (e.getSource() == Kup)
		{
			kupowanie();
			framen.dispose();

		}
		if (e.getSource() == Z)
		{
			if (ile_dni_wazny(PImie.getText(),PNazwisko.getText()) == null)
			{
				d = "Brak klienta w bazie";	
				W.setText(d);
			}
			else
			{
				String ilosc = boks.getSelectedItem().toString();
				przedluz(PImie.getText(),PNazwisko.getText(),Integer.valueOf(ilosc));	
				d = "Zakupiono";
				try {
					WriteToFile(rodzaj);
				} catch (FileNotFoundException en) {
					System.out.println("NIE ZNAEZIONO PLIKU");
				}
				W.setText(d);
			}
		}
		if (e.getSource() == Wroc){
			Edycja();
			frame.dispose();
		}
		if (e.getSource() == Rej){
			rej();
			frame.dispose();
		}
		if (e.getSource() == Wrocr){
			kupowanie();
			framer.dispose();
		}
		if (e.getSource() == POTW){
			dodaj(PImie.getText(),PNazwisko.getText(),"2001-01-01","2001-01-01",Integer.valueOf(PWiek.getText()),PPesel.getText());
			try {
				WriteToFile(rodzaj);
			} catch (FileNotFoundException en) {
				System.out.println("NIE ZNAEZIONO PLIKU");
			}
			d = "Dodano do bazy";
			W.setText(d);
		}
	}	
}	

