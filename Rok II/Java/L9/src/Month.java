
import java.awt.*;
import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;

public class Month extends JPanel {
	
	public JButton button;
	public JTable table;
	private final String[] columns = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	public Object[][] data = {{423,null,null,null,null,null,null},{null,null,null,null,null,null,null},{null,null,null,null,null,null,null},
			{null,null,null,null,null,null,null},{null,null,null,null,null,null,null}};
	
	public Month(String name) {
		setLayout(new BorderLayout());
		button = new JButton(name);
		table = new JTable(data, columns);
		table.getColumnModel().getColumn(6).setCellRenderer(new StatusColumnCellRenderer());
		add(BorderLayout.PAGE_START, button);
		add(new JScrollPane(table));
		setVisible(true);
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
