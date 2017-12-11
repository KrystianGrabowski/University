import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.util.GregorianCalendar;
import java.util.LinkedList;
import java.util.List;

import javax.swing.*;


public class Calendar extends JFrame {
	
	private GregorianCalendar gc;
	public JTabbedPane panelMain = new JTabbedPane();
	public JPanel panelYear = new JPanel();
	public MonthList panelMonth;
	public JToolBar tb;
	public JLabel year, month;
	public JSpinner yearSp, monthSp;
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
		year = new JLabel("Year:");
		month = new JLabel("Month:");
		tb.add(year);
		SpinnerModel model_y = new SpinnerNumberModel( gc.get(GregorianCalendar.YEAR), 1582, null , 1);
		yearSp = new JSpinner(model_y);
		tb.add(yearSp);
		
		tb.add(month);
		SpinnerModel model_m = new LoopSpinner (months, yearSp);	
		monthSp = new JSpinner(model_m);
		monthSp.setValue(months[gc.get(GregorianCalendar.MONTH)]);
		tb.add(monthSp);


	}
	
	public class LoopSpinner extends SpinnerListModel{
		JSpinner spinner; 
		
		public LoopSpinner(String[] months, JSpinner spinner) {
			super(months);
			this.spinner = spinner;
		}
		
		public Object getNextValue() {
			List list = getList();
            int index = list.indexOf(getValue());
            if (index == list.size() - 1) {
            	index = 0;
            	
            }
            else {
            	index++;
            }
            return list.get(index);
		}
		
		public Object getPreviousValue() {
			List list = getList();
			int index = list.indexOf(getValue());
			if (index == 0) {
				index = list.size() - 1;
			}
			else {
				index--;
			}
			return list.get(index);
			
		}
	}

}
