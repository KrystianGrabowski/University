
import java.awt.*;
import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import java.util.GregorianCalendar;


public class Month extends JPanel {
	
	public JButton button;
	public JTable table;
	private final String[] columns = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	private final String[] columns2 = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	public Object[][] data = {{null,null,null,null,null,null,null},{null,null,null,null,null,null,null},{null,null,null,null,null,null,null},
			{null,null,null,null,null,null,null},{null,null,null,null,null,null,null}, {null,null,null,null,null,null,null}};
	private final int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	private final String[] months = {"January", "February", "March", "April",
			"May", "June", "July", "August",
			"September","October", "November", "December"};
	GregorianCalendar gc;
	public JTabbedPane jtp;
	public MonthList ml;
	public JSpinner jspinner, jspinnerm;
	
	public Month(String name, int month, int year, JTabbedPane jtb, MonthList mlds, JSpinner spinner, JSpinner spinnerm) {
		this.jtp = jtb;
		this.ml = mlds;
		this.jspinner = spinner;
		this.jspinnerm = spinnerm;
		setLayout(new BorderLayout());
		button = new JButton(name);
		button.addActionListener(event -> {
			String m = event.getActionCommand();
			int r = (int) spinner.getValue();
			spinnerm.setValue(m);
			ml.change(toNum(m) + 1, r);
			jtp.setSelectedIndex(1);
			jtp.setTitleAt(1, months[month]);
			
		});
		setdays(month, year);
		table = new JTable(data, columns);
		table.getColumnModel().getColumn(6).setCellRenderer(new StatusColumnCellRenderer());
		add(BorderLayout.PAGE_START, button);
		add(new JScrollPane(table));
		setVisible(true);
	}

	public int toNum(String name) {
		int m = 0;
		for (String month : months) {
			if (month.equals(name)) {
				return m;
			}
			else {
				m++;
			}
		}
		return m;
	}
	public void setdays( int month, int year) {
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

		for (Object[] el : data) {
			for (int o = 0; o < 7; o++) {
				el[o] = null;
			}
		}
		gc = new GregorianCalendar(year,month,1);
		int off = gc.get(GregorianCalendar.DAY_OF_WEEK);
		if (off == 1) {
			off = 6;
		}
		else {
			off = off - 2;
		}
		if (year == 1582 && month == 9) {
			int i = 1;
			for (Object[] el : data) {
				for (int p = 0; p < 7; p++) {
					
					if(off > 0) {
						el[p] = null;
						off--;
					}
					else {
						if (i <= hwm) {
							el[p] = i;
							if (i == 4) {
								i = 15;
							}
							else {
								i++;
							}			
						}
						else {
							break;
						}

					}
					
				}
			}
		}
		else {
			int i = 1;
			for (Object[] el : data) {
				for (int p = 0; p < 7; p++) {
					if(off > 0) {
						el[p] = null;
						off--;
					}
					else {
						if (i <= hwm) {
							el[p] = i;
							i++;					
						}
						else {
							break;
						}

					}
					
				}
			}			
		}

	}
	
	public class StatusColumnCellRenderer extends DefaultTableCellRenderer {
		@Override
		  public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int col) {
            JLabel l = (JLabel) super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, col);
            l.setBackground(new Color(255, 31, 50));
            return l;

			}
		}
}
