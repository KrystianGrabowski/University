import java.awt.*;
import java.awt.event.*;
import java.util.LinkedList;
import java.util.List;

public class Ramka extends Frame {
	
	public Canvas canvas = new Canvas();
	public Panel menu;
	public Color c1 = Color.RED;
	private List<Kreska> lista;
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
        		lista.add(new Kreska(pointStart, pointEnd, Color.BLACK));
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
		menu_();
		this.lista = new LinkedList<>();
		setLayout(new BorderLayout());
		
		add(canvas, BorderLayout.CENTER);
        canvas.addMouseListener(mouseList);
        canvas.addMouseMotionListener(mml);
        canvas.addMouseListener(mouseList);
        canvas.setFocusable(true);
        canvas.requestFocus();
        
		add(menu, BorderLayout.WEST);
		setVisible(true);
        addWindowListener(frameList);


	}
	
	public void menu_() {
		menu = new Panel(new BorderLayout());
		menu.setBackground(Color.GRAY);
		Checkbox chk = new Checkbox("Czerwony",true);
		menu.add(chk);
		 
	}
	public void paint(Graphics g) 
	{
		g = canvas.getGraphics();

		g.clearRect(0, 0, getWidth(), getHeight());
        g.setColor(Color.RED);
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
	
}


