import java.awt.*;
import javax.swing.*;

import java.util.ArrayList;
import java.util.GregorianCalendar;


public class MonthList extends JPanel {
	private final String[] months = {"January", "February", "March", "April",
			"May", "June", "July", "August",
			"September","October", "November", "December"};
	private final int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	public JList<String>  listPrev, list, listNext;
	private GregorianCalendar gc = new GregorianCalendar();
	
	public MonthList(String name) {


		setLayout(new GridLayout(1,3));
		add(listPrev);
		add(list);
		add(listNext);
		
		setVisible(true);
	}

	public MonthList() {
		listPrev = new JList<String>();
		list = new JList<String>();
		listNext = new JList<String>();
		ArrayList<String> lista = new ArrayList<>();
		String[] nextmonth = new String[50];
		String[] prevmonth = new String[50];
		String[] actualmonth = new String[50];
		
		Integer i = (gc.get(GregorianCalendar.MONTH));
		System.out.println(i);
		actualmonth[0] = months[i];
		
		if (i < 11) {
			nextmonth[0] = months[i + 1]; 			
		}
		else {
			nextmonth[0] = months[0];
		}
		if (i > 0) {
			System.out.println("SDASD");
			prevmonth[0] = months[i - 1];		
		}
		else {
			prevmonth[0] = months[11];
		}
		

		listPrev = new JList<String>(prevmonth);
		list = new JList<String>(actualmonth);
		listNext = new JList<String>(nextmonth);
		
		setLayout(new GridLayout(1,3));
		add(new JScrollPane(listPrev));
		add(new JScrollPane(list));
		add(new JScrollPane(listNext));
		setVisible(true);
	}


}
