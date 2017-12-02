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

        scrolled = Gtk.ScrolledWindow()
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        #self.add(scrolled)

        self.artists = Gtk.Box(spacing = 5)
        self.artists.set_size_request(150,150)
        self.grid.add(self.artists)
        self.load_artists()

        self.albums = Gtk.ListBox()
        self.grid.attach_next_to(self.albums, self.artists, Gtk.PositionType.BOTTOM,30,50)

        self.tracks = Gtk.ListBox()
        self.grid.attach_next_to(self.tracks, self.albums, Gtk.PositionType.RIGHT, 50,50)

        self.hb = Gtk.HeaderBar()
        self.hb.set_show_close_button(True)
        self.hb.props.title = "Records"
        self.set_titlebar(self.hb)

"""    def load(self,widget):

        self.button0 = Gtk.Label("buttonziro")
        self.listbox1 = Gtk.ListBox()
        self.grid.attach_next_to(self.listbox1, self.listbox, Gtk.PositionType.RIGHT, 50,50)
        self.listbox1.add(self.button0)
        self.show_all()
        #self.listbox1.unselect_all()"""


window = Music()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
