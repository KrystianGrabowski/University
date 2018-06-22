import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;


public class WydawnictwoCiagle extends Ksiazka {
	
	public WydawnictwoCiagle(String x, String y, int z)
	{
		super(x,y,z);
		
	}
	public void Edycja()
	{
		JFrame frame = new JFrame("Edycja wydawncitwaCiaglego");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		Container kontener = frame.getContentPane();
		GridLayout layout = new GridLayout(4, 2);
		kontener.setLayout(layout);
		
		JLabel autor_etykieta = new JLabel("Autor");
		kontener.add(autor_etykieta);
		PAutor = new JTextField(this.autor, 40);
		kontener.add(PAutor);
		
		JLabel tytu³_etykieta = new JLabel("Tytu³");
		kontener.add(tytu³_etykieta);
		PTytul = new JTextField(this.tytul, 40);
		kontener.add(PTytul);
		
		JLabel wydanie_etykieta = new JLabel("Wydanie");
		kontener.add(wydanie_etykieta);
		PRok = new JTextField(Integer.toString(this.rok_wydania), 40);
		kontener.add(PRok);
		
		JButton b = new JButton("Zapisz");
		b.addActionListener(this);
		kontener.add(b);
		
		frame.pack();
		frame.setVisible(true);

	}

	public void actionPerformed(ActionEvent e) {
		
		this.autor = PAutor.getText();
		this.tytul = PTytul.getText();
		this.rok_wydania = Integer.parseInt(PRok.getText());
		

		
	}

}
