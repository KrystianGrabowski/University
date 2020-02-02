import java.awt.*;
import javax.swing.*;

import java.util.ArrayList;
import java.util.GregorianCalendar;


public class MonthList extends JPanel {
	private final String[] months = {"January", "February", "March", "April",
			"May", "June", "July", "August",
			"September","October", "November", "December"};

	public JList<String>  listPrev, list, listNext;
	String[] nextmonth;
	String[] prevmonth;
	String[] actualmonth;
	Integer pm, am, nm;
	Integer pmy, amy, nmy;
	public Model modelprev, modelactual, modelnext;


	
	public MonthList(int m, int y) {
		listPrev = new JList<String>();
		list = new JList<String>();
		listNext = new JList<String>();
		nextmonth = new String[32];
		prevmonth = new String[32];
		actualmonth = new String[32];
		month_choose(m ,y);
		
		actualmonth[0] = months[am];
		nextmonth[0] = months[nm];
		prevmonth[0] = months[pm];
		
		modelprev = new Model(pmy, pm);
		modelactual = new Model(amy, am);
		modelnext = new Model(nmy,nm);
		listPrev = new JList<String>(modelprev);
		listPrev.setCellRenderer(new Render());
		list = new JList<String>(modelactual);
		list.setCellRenderer(new Render());
		listNext = new JList<String>(modelnext);	
		listNext.setCellRenderer(new Render());
		
		setLayout(new GridLayout(1,3));
		add(new JScrollPane(listPrev));
		add(new JScrollPane(list));
		add(new JScrollPane(listNext));
		setVisible(true);
	}
	
	public void change(int m, int y) {
		month_choose(m,y);
		modelprev.changeModel(pmy, pm);
		modelactual.changeModel(amy, am);
		modelnext.changeModel(nmy, nm);
		
	}
	
	public void month_choose(int m, int y) {
		am = m-1;
		amy = y;
		if (m < 12) {
			nextmonth[0] = months[m];
			nm = m;
			nmy = y;
		}
		else {
			nm = 0;
			nmy = y + 1;
		}
		if (m > 1) {
			pm = m-2;
			pmy = y;
		}
		else {
			pm = 11;
			pmy = y - 1;
		}		
	}


}
