import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class Music(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title = "Music")
        self.set_default_size(1024,700)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(10)
        self.grid.set_column_spacing(10)
        self.add(self.grid)
        button1 = Gtk.Button(label ="Button 1")
        button2 = Gtk.Button(label="Button 2")
        button3 = Gtk.Button(label="Button 3")
        button4 = Gtk.Button(label="Button 4")
        button5 = Gtk.Button(label="Button 5")
        button6 = Gtk.Button(label="Button 6")

        scrolled = Gtk.ScrolledWindow()
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        #self.add(scrolled)

        self.box = Gtk.Box(spacing = 5)
        self.box.set_size_request(150,150)
        self.box.pack_start(button3, True, True, 0)
        button3.connect("clicked", self.load)
        self.box.pack_start(button4, True, True, 0)
        self.grid.add(self.box)

        self.listbox = Gtk.ListBox()
        self.listbox.add(button5)
        self.listbox.add(button6)
        self.grid.attach_next_to(self.listbox,self.box, Gtk.PositionType.BOTTOM,30,50)
        #self.grid.attach(self.listbox,500,500,10,10)

        self.listbox1 = Gtk.ListBox()
        self.grid.attach_next_to(self.listbox1, self.listbox, Gtk.PositionType.RIGHT, 50,50)

        self.hb = Gtk.HeaderBar()
        self.hb.set_show_close_button(True)
        self.hb.props.title = "records"
        self.set_titlebar(self.hb)

    def load(self,widget):

        self.button0 = Gtk.Label("buttonziro")
        self.listbox1 = Gtk.ListBox()
        self.grid.attach_next_to(self.listbox1, self.listbox, Gtk.PositionType.RIGHT, 50,50)
        self.listbox1.add(self.button0)
        self.show_all()
        #self.listbox1.unselect_all()


window = Music()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
