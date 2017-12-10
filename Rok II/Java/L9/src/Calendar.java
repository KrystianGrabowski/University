import java.awt.GridLayout;
import java.util.LinkedList;

import javax.swing.*;

public class Calendar extends JFrame {
	
	public JTabbedPane panelMain = new JTabbedPane();
	public JPanel panelYear = new JPanel();
	public MonthList panelMonth;
	private final String[] months = {"January", "February", "March", "April",
									"May", "June", "July", "August",
									"September","October", "November", "December"};
	
	public Calendar() {
		super("Calendar");
		
		setSize(800,600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo( null );
		panels();
		panelMonth = new MonthList(2, 2017);
		panelMain.addTab("Miesiac", panelMonth);

		add(panelMain);
		
        setVisible(true);
	}
	
	void panels() {
		
		panelYear.setLayout(new GridLayout(4, 3));
		
		for(String m : months){
			panelYear.add(new Month(m));
		}
		
		
		panelMain.addTab("Rok", panelYear);		
	}

}
