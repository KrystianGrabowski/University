import java.awt.BorderLayout;

import javax.swing.*;

public class Month extends JPanel {
	
	public JButton button;
	public JLabel lb = new JLabel("LAAABBBEEELL");
	public JTable table;
	private final String[] columns = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	public Object[][] data = {{423,null,null,null,null,null,null},{null,null,null,null,null,null,null},{null,null,null,null,null,null,null},
			{null,null,null,null,null,null,null},{null,null,null,null,null,null,null}};
	public Month(String name) {
		setLayout(new BorderLayout());
		button = new JButton(name);
		table = new JTable(data, columns);
		
		add(BorderLayout.PAGE_START, button);
		add(new JScrollPane(table));
		setVisible(true);
	}
}
