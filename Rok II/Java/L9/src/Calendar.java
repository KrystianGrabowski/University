import java.awt.GridLayout;

import javax.swing.*;

public class Calendar extends JFrame {
	
	JTabbedPane panelMain = new JTabbedPane();
	JPanel panelYear = new JPanel();
	JPanel panelMonth = new JPanel();

	
	public Calendar() {
		super("Calendar");
		setSize(800,600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo( null );
		panels();
		add(panelMain);
		
        setVisible(true);
	}
	
	void panels() {
		
		panelYear.setLayout(new GridLayout(4, 3));
		
		panelYear.add(new JLabel("Label1"));
		panelYear.add(new JLabel("Label2"));
		
		
		panelMain.addTab("Rok", panelYear);
		panelMain.addTab("Miesiac", panelMonth);
		
	}

}
