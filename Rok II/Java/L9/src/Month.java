
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
			{null,null,null,null,null,null,null},{null,null,null,null,null,null,null}};
	private final int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	private final String[] months = {"January", "February", "March", "April",
			"May", "June", "July", "August",
			"September","October", "November", "December"};
	GregorianCalendar gc;
	public JTabbedPane jtp;
	
	public Month(String name, int month, int year, JTabbedPane jtb) {
		this.jtp = jtb;
		setLayout(new BorderLayout());
		button = new JButton(name);
		button.addActionListener(event -> {
			String m = event.getActionCommand();
			jtp.setSelectedIndex(1);

		});
		setdays(month, year);
		table = new JTable(data, columns);
		table.getColumnModel().getColumn(6).setCellRenderer(new StatusColumnCellRenderer());
		add(BorderLayout.PAGE_START, button);
		add(new JScrollPane(table));
		setVisible(true);
	}
	public int toNum(String month) {
		int m = 0, i=0;
		for (String mth : months) {
			if (mth.equals(month)) {
				m = i;
			}
			else {
				i++;
			}
		}
		return m;
	}
	
	public void setdays( int month, int year) {
		gc = new GregorianCalendar(year,month,1);
		int off = gc.get(GregorianCalendar.DAY_OF_WEEK);
		if (off == 1) {
			off = 6;
		}
		else {
			off = off - 2;
		}
		int i = 1;
		for (Object[] el : data) {
			for (int p = 0; p < 7; p++) {
				if(off > 0) {
					el[p] = null;
					off--;
				}
				else {
					if (i <= days[month]) {
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
	
	public class StatusColumnCellRenderer extends DefaultTableCellRenderer {
		@Override
		  public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int col) {
            JLabel l = (JLabel) super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, col);
            l.setBackground(new Color(255, 31, 50));
            return l;

			}
		}
}
