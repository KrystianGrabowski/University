import java.awt.*;
import javax.swing.*;

import java.util.ArrayList;
import java.util.GregorianCalendar;


public class MonthList extends JPanel {
	private final String[] months = {"January", "February", "March", "April",
			"May", "June", "July", "August",
			"September","October", "November", "December"};
	private final int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	private final String[] columns = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	private final String[] columns2 = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	public JList<String>  listPrev, list, listNext;
	String[] nextmonth;
	String[] prevmonth;
	String[] actualmonth;
	Integer pm, am, nm;
	Integer pmy, amy, nmy;
	private GregorianCalendar gc;
	private GregorianCalendar gc_d;
	public Model modelprev, modelactual, modelnext;


	
	public MonthList(Integer m, Integer y) {
		listPrev = new JList<String>();
		list = new JList<String>();
		listNext = new JList<String>();
		nextmonth = new String[32];
		prevmonth = new String[32];
		actualmonth = new String[32];
		
		actualmonth[0] = months[m - 1];
		am = m-1;
		amy = y;
		if (m < 12) {
			nextmonth[0] = months[m];
			nm = m;
			nmy = y;
		}
		else {
			nextmonth[0] = months[0];
			nm = 0;
			nmy = y + 1;
		}
		if (m > 1) {
			prevmonth[0] = months[m - 2];
			pm = m-2;
			pmy = y;
		}
		else {
			prevmonth[0] = months[11];
			pm = 11;
			pmy = y - 1;
		}
		
		modelprev = new Model(pmy, pm);
		modelactual = new Model(amy, am);
		modelnext = new Model(nmy,nm);
		listPrev = new JList<String>(modelprev);
		list = new JList<String>(modelactual);
		listNext = new JList<String>(modelnext);	
		
		setLayout(new GridLayout(1,3));
		add(new JScrollPane(listPrev));
		add(new JScrollPane(list));
		add(new JScrollPane(listNext));
		setVisible(true);
	}

	public MonthList() {
		gc = new GregorianCalendar();
		listPrev = new JList<String>();
		list = new JList<String>();
		listNext = new JList<String>();
		nextmonth = new String[50];
		prevmonth = new String[50];
		actualmonth = new String[50];
		
		Integer i = (gc.get(GregorianCalendar.MONTH));
		
		actualmonth[0] = months[i];
		
		if (i < 11) {
			nextmonth[0] = months[i + 1]; 			
		}
		else {
			nextmonth[0] = months[0];
		}
		if (i > 0) {
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
	/*public void days(Integer m, Integer y) {
		Integer whichday;
		gc_d = new GregorianCalendar(amy,am,1);
		whichday = (gc_d.get(GregorianCalendar.DAY_OF_WEEK));
		for (int j = 1; j <= days[am]; j++) {
			String combo = String.valueOf(j) + columns2[(whichday - 1) % 7];
			actualmonth[j] = combo;
			whichday++;
		}
		System.out.println(pmy);
		gc_d = new GregorianCalendar(pmy,pm,1);
		whichday = (gc_d.get(GregorianCalendar.DAY_OF_WEEK));
		for (int j = 1; j <= days[pm]; j++) {
			String combo = String.valueOf(j) + columns2[(whichday - 1) % 7];
			prevmonth[j] = combo;
			whichday++;
		}
		gc_d = new GregorianCalendar(nmy,nm,1);
		whichday = (gc_d.get(GregorianCalendar.DAY_OF_WEEK));
		for (int j = 1; j <= days[nm]; j++) {
			String combo = String.valueOf(j) + columns2[(whichday - 1) % 7];
			nextmonth[j] = combo;
			whichday++;
		}*/


}
