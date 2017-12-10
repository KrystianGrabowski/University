import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.util.GregorianCalendar;
import java.util.LinkedList;

import javax.swing.*;


public class Calendar extends JFrame {
	
	private GregorianCalendar gc;
	public JTabbedPane panelMain = new JTabbedPane();
	public JPanel panelYear = new JPanel();
	public MonthList panelMonth;
	public JToolBar tb;
	private final String[] months = {"January", "February", "March", "April",
									"May", "June", "July", "August",
									"September","October", "November", "December"};
	
	public Calendar() {
		super("Calendar");
		setLayout(new BorderLayout());
		gc = new GregorianCalendar();
		setSize(800,600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo( null );
		panel(gc.get(GregorianCalendar.YEAR));
		toolbr();
		panelMonth = new MonthList(gc.get(GregorianCalendar.MONTH) + 1, gc.get(GregorianCalendar.YEAR));

		
		panelMain.addTab("Miesiac", panelMonth);

		add(BorderLayout.CENTER, panelMain);
		add(BorderLayout.PAGE_END, tb);
        setVisible(true);
	}
	
	void panel(int year) {
		panelYear.setLayout(new GridLayout(4, 3));	
		int i = 0;
		for(String m : months){
			panelYear.add(new Month(m, i ,year));
			i++;
		}
		panelMain.addTab("Rok", panelYear);		
	}
	public void toolbr() {
		tb = new JToolBar();
		tb.setLayout(new FlowLayout());
		JLabel j = new JLabel("ADSS");
		tb.add(j);
	}

}
