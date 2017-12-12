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
		if (year == 1582 && month == 9) {
			for (int j = 1; j <= 4; j++) {
				list.add(new Object[]{columns2[(whichday - 1) % 7], j, months[month]});
				whichday++;
			}		
			for (int j = 15; j <= 31; j++) {
				list.add(new Object[]{columns2[(whichday - 1) % 7], j, months[month]});
				whichday++;
			}			
		}
		else {
			int hwm = 0;
			if (month == 1) {
				if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
					hwm = days[month] + 1;
				}
				else {
					hwm = days[month];
				}
			
			}
			else {
				hwm = days[month];
			}
			
			for (int j = 1; j <= hwm; j++) {
				list.add(new Object[]{columns2[(whichday - 1) % 7], j, months[month]});
				whichday++;				
			

			}
		}
	}
	
	@Override
	public int getSize() {
		if (year == 1582 && month == 9) {
			return days[month] - 9;
		}
		if (month == 1) {
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
				return days[month] + 2;
			}
		}
		return days[month] + 1 ;			

	}
	
	@Override
	public Object getElementAt(int index) {
		return list.get(index);

		
	}

}
