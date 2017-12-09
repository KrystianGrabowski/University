import java.awt.GridLayout;
import java.util.LinkedList;

import javax.swing.*;

public class Calendar extends JFrame {
	
	public JTabbedPane panelMain = new JTabbedPane();
	public JPanel panelYear = new JPanel();
	public JPanel panelMonth = new JPanel();
	private final String[] months = {"January", "February", "March", "April",
									"May", "June", "July", "August",
									"September","October", "November", "December"};
	
	public Calendar() {
		super("Calendar");
		
		setSize(1000,800);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo( null );
		panels();
		add(panelMain);
		
        setVisible(true);
	}
	
	void panels() {
		
		panelYear.setLayout(new GridLayout(4, 3));
		
		for(String m : months){
			panelYear.add(new Month(m));
		}
		
		
		panelMain.addTab("Rok", panelYear);
		panelMain.addTab("Miesiac", panelMonth);
		
	}

}
