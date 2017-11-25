import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk, GdkPixbuf


class Im(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Images")
        self.set_default_size(800,600)
        self.grid = Gtk.Grid()
        self.add(self.grid)

        self.hb = Gtk.HeaderBar()
        self.hb.set_show_close_button(True)
        self.hb.props.title = "Images"
        self.set_titlebar(self.hb)

        self.button = Gtk.Button(label = "Load")
        self.button.connect("clicked", self.load)
        self.hb.pack_end(self.button)


        self.imafff = Gtk.Image()
        self.grid.add(self.imafff)

    def load(self, widget):
        dialog = Gtk.FileChooserDialog("Select", self, Gtk.FileChooserAction.OPEN,
                                        ("Cancel", Gtk.ResponseType.CANCEL,
                                        "Open", Gtk.ResponseType.OK))
        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            path = dialog.get_filename()
            pixbuf = GdkPixbuf.Pixbuf().new_from_file(path)
            print(path)
            pixbuf2 = pixbuf.scale_simple(800,600,GdkPixbuf.InterpType.BILINEAR)
            self.imafff.set_from_pixbuf(pixbuf2)
        elif response == Gtk.ResponseType.CANCEL:
            print("Cancel selected")


        dialog.destroy()




window = Im()
window.connect("delete-event", Gtk.main_quit)
window.show_all();
Gtk.main()
