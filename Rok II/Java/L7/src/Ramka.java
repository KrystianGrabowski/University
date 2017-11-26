import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Ramka extends Frame {
	public Ramka() {

		setSize(800, 600);
		setVisible(true);
		Listeners_();
		
		setLayout(new BorderLayout());
		
		
	}
	
	private void Listeners_() {
		
        addWindowListener(new WindowAdapter(){  
            public void windowClosing(WindowEvent e) {  
                dispose();  
            }  
        });  		
	}
}
