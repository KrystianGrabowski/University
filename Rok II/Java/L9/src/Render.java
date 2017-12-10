import java.awt.Color;
import java.awt.Component;

import javax.swing.BorderFactory;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;

public class Render implements ListCellRenderer{
	 protected DefaultListCellRenderer defaultRenderer = new DefaultListCellRenderer();
	@Override
    public Component getListCellRendererComponent(JList list, Object value, int index,
              boolean isSelected, boolean cellHasFocus) {
		Color foreground = null;
        String settext = null;
		JLabel renderer = (JLabel) defaultRenderer.getListCellRendererComponent(list, value, index,
		        isSelected, cellHasFocus);
		 if (value instanceof Object[]) {
			 
			 Object[] text = (Object[]) value;
			 if (text[0].equals(-1)) {
				 settext = String.valueOf(text[2]);
				 foreground = Color.GREEN;
			 }
			 
			 else{
				 settext = String.valueOf(text[1]) + " " + String.valueOf(text[0]);
				 if (text[0].equals("Sunday")) {
					 foreground = Color.RED;
				 }
				 else {
					 foreground = Color.BLACK;
					 
				 }				 
			 }

			 
		 }
	     renderer.setText(settext);
	     renderer.setForeground(foreground);
		 return renderer;	
	}

}
