import java.util.ArrayList;
import java.util.GregorianCalendar;
import java.util.List;

import javax.swing.AbstractListModel;

public class Model extends AbstractListModel {
	private int year;
	private int month;
	private final String[] columns2 = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	private final String[] months = {"January", "February", "March", "April",
			"May", "June", "July", "August",
			"September","October", "November", "December"};
	private final int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	public ArrayList<Object[]> list;
	private GregorianCalendar gc;
	
	public Model(int year, int month) {
		this.month = month;
		this.year = year;
		list = new ArrayList<>();
		set(year, month);
	}
	
	public void changeModel(int year, int month) {
		this.year = year;
		this.month = month;
		list = new ArrayList<>();
		set(year, month);
		fireContentsChanged(this, 0, getSize() - 1);
		
	}
	
	public void set(int year, int month) {
		gc = new GregorianCalendar(year, month, 1);
		int whichday = (gc.get(GregorianCalendar.DAY_OF_WEEK));
		list.add(new Object[] {-1,-1,months[month]});
		for (int j = 1; j <= days[month]; j++) {
			list.add(new Object[]{columns2[(whichday - 1) % 7], j, months[month]});
			whichday++;
		}
	}
	
	@Override
	public int getSize() {
		return days[month] + 1 ;
	}
	
	@Override
	public Object getElementAt(int index) {
		return list.get(index);

		
	}

}
