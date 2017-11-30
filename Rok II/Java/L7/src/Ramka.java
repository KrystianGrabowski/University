import java.awt.*;
import java.awt.event.*;
import java.util.LinkedList;
import java.util.List;

public class Ramka extends Frame {
	
	public Canvas canvas = new Canvas();
	public Panel panel;
	public Color c1 = Color.BLACK;
	public Color c2 = Color.GREEN;
	public Color c3 = Color.YELLOW;
	public Color c4 = Color.RED;
	public Color c5 = Color.BLUE;
	public Color AC = c1;
	private LinkedList<Kreska> lista;
	private Point pointStart = new Point();
	private Point pointEnd = new Point();
	private Point pointTemp = new Point();

	
		
    private WindowListener frameList = new WindowAdapter()
    {
    	@Override
    	public void windowClosing (WindowEvent ev)
    	{
        	Ramka.this.dispose();
    	}
    };
    
    private MouseListener mouseList = new MouseAdapter()
    {
        @Override
        public void mousePressed(MouseEvent ev)
        {
    		pointEnd = ev.getPoint();
            pointStart = ev.getPoint();
        }
        @Override
        public void mouseReleased(MouseEvent ev)
        {
        	if(points_ok(pointStart, pointEnd))
        		lista.add(new Kreska(pointStart, pointEnd, AC));
        	pointStart = new Point();
        	pointEnd = new Point();
        	pointTemp = null;
        	
            repaint();
        }
    };
    
    private boolean points_ok(Point x1, Point x2) {
    	if (x1.x < 0 || x1.x > getWidth() || x2.x < 0 || x2.x > getWidth())
    		return false;
    	if (x1.y < 0 || x1.y > getHeight() || x2.y < 0 || x2.y > getHeight())
    		return false;
    	if (x1.x == x2.x && x1.y == x2.y)
    		return false;
    	return true;
    }
    
    private MouseMotionListener mml = new MouseMotionAdapter() 
    {

    	@Override
        public void mouseDragged(MouseEvent ev) {
            
    		pointTemp = ev.getPoint();
    		pointEnd = ev.getPoint();
            
            repaint();

        }
    };

    
	
	
	public Ramka() {

		super("Kreski");
		setSize(800, 600);
		wybor_();
		
		this.lista = new LinkedList<>();
		setLayout(new BorderLayout());
		add(panel, BorderLayout.WEST);
		add(canvas, BorderLayout.CENTER);
        canvas.addMouseListener(mouseList);
        canvas.addMouseMotionListener(mml);
        canvas.addMouseListener(mouseList);
        canvas.addKeyListener(k);
        canvas.setFocusable(true);
        canvas.requestFocus();
        
		
		setVisible(true);
        addWindowListener(frameList);


	}
	
	public void wybor_() {
		panel = new Panel(new BorderLayout());
		panel.setBackground(Color.GRAY);
		
		Panel kolory = new Panel(new GridLayout(5,1));
		
		CheckboxGroup cbg = new CheckboxGroup();		
		Checkbox chck1 = new Checkbox("Czarny", cbg, false);
		Checkbox chck2 = new Checkbox("Zielony", cbg, false);
		Checkbox chck3 = new Checkbox("Żółty", cbg, false);
		Checkbox chck4 = new Checkbox("Czerwony", cbg, false);
		Checkbox chck5 = new Checkbox("Niebieski", cbg, false);
		kolory.add(chck1);
		kolory.add(chck2);
		kolory.add(chck3);
		kolory.add(chck4);		
		kolory.add(chck5);
		
		panel.add(kolory, BorderLayout.SOUTH);
	    chck1.addItemListener(new ItemListener() {
	        public void itemStateChanged(ItemEvent e) {
	        	AC = c1;
	        }
	     });

	    chck2.addItemListener(new ItemListener() {
	        public void itemStateChanged(ItemEvent e) {
	        	AC = c2;
	        }
	     });
	    chck3.addItemListener(new ItemListener() {
	        public void itemStateChanged(ItemEvent e) {
	        	AC = c3;
	        }
	     });
	    chck4.addItemListener(new ItemListener() {
	        public void itemStateChanged(ItemEvent e) {
	        	AC = c4;
	        }
	     });
	    chck5.addItemListener(new ItemListener() {
	        public void itemStateChanged(ItemEvent e) {
	        	AC = c5;
	        }
	     });
	    
	     
	}
	
	public void clear() {
		lista = new LinkedList<>();
		repaint();
	}
	
	public void dellast() {
		lista.removeLast();
		repaint();
	}
	
	public void delfirst() {
		lista.remove(0);
		repaint();
	}
	
	public void paint(Graphics g) 
	{
		g = canvas.getGraphics();

		g.clearRect(0, 0, getWidth(), getHeight());
        g.setColor(AC);
        for (Kreska p : lista) {
            g.setColor(p.kolor);
            g.drawLine(p.poczatek.x, p.poczatek.y, p.koniec.x, p.koniec.y);
        }

        if (pointTemp != null) {
            g.setColor(Color.GRAY);
            g.drawLine(pointStart.x, pointStart.y, pointTemp.x, pointTemp.y);

        }
	

	g.dispose();
	
	}
	KeyListener k = new KeyListener();
	public class KeyListener extends KeyAdapter {
		
		@Override
		public void keyReleased(KeyEvent e) {
			switch (e.getKeyCode()) {
			case KeyEvent.VK_B:
				dellast();
			case KeyEvent.VK_L:
				dellast();
			case KeyEvent.VK_BACK_SPACE:
				clear();
			case KeyEvent.VK_F:
				delfirst();
			}

		}
	}
	
}


