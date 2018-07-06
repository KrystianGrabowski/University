import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk, GdkPixbuf


class Im(Gtk.Window):
    def __init__(self):

        self.tab = []
        self.size = -1
        self.i = -1

        Gtk.Window.__init__(self, title="Images")
        self.set_default_size(800,600)
        self.grid = Gtk.Grid()
        self.add(self.grid)

        self.hb = Gtk.HeaderBar()
        self.hb.set_show_close_button(True)
        self.hb.props.title = "Images"
        self.set_titlebar(self.hb)

        button = Gtk.Button(label = "Load")
        button.connect("clicked", self.load)
        self.hb.pack_end(button)

        button_next = Gtk.Button(label = "Next")
        button_next.connect("clicked", self.next_f)
        self.hb.pack_end(button_next)

        button_prev = Gtk.Button(label = "Prev")
        button_prev.connect("clicked", self.prev_f)
        self.hb.pack_start(button_prev)


        self.imafff = Gtk.Image()
        self.grid.add(self.imafff)

    def next_f(self, widget):
        if (self.i < self.size):
            self.i += 1
            self.show_f(self.i)

    def prev_f(self, widget):
        if (self.i > 0 ):
            self.i -= 1
            self.show_f(self.i)


    def show_f(self, nr):
            pixbuf = GdkPixbuf.Pixbuf().new_from_file(self.tab[nr])
            pixbuf2 = pixbuf.scale_simple(800,600,GdkPixbuf.InterpType.BILINEAR)
            self.imafff.set_from_pixbuf(pixbuf2)

    def load(self, widget):
        dialog = Gtk.FileChooserDialog("Select", self, Gtk.FileChooserAction.OPEN,
                                        ("Cancel", Gtk.ResponseType.CANCEL,
                                        "Open", Gtk.ResponseType.OK))
        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            path = dialog.get_filename()
            self.tab.append(path)
            self.size += 1
            self.i = self.size
            pixbuf = GdkPixbuf.Pixbuf().new_from_file(path)
            pixbuf2 = pixbuf.scale_simple(800,600,GdkPixbuf.InterpType.BILINEAR)
            self.imafff.set_from_pixbuf(pixbuf2)
        dialog.destroy()


window = Im()
window.connect("delete-event", Gtk.main_quit)
window.show_all();
Gtk.main()
