import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk


class Im(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Images")

        self.grid = Gtk.Grid()
        self.add(self.grid)

        self.button = Gtk.Button(label = "Choose file")
        self.button.connect("clicked", self.choose_image)
        self.grid.add(self.button)
        """
        self.frame = Gtk.Frame(label = "Image")
        self.frame.set_label_align(23, 23)
        self.frame.set_shadow_type(Gtk.ShadowType.IN)
        self.grid.attach_next_to(self.frame, self.button,
                         Gtk.PositionType.RIGHT, 1, 1)
        """
        self.imafff = Gtk.Image()
        self.grid.attach_next_to(self.imafff, self.button,
                         Gtk.PositionType.RIGHT, 1, 1)

    def choose_image(self, widget):
        dialog = Gtk.FileChooserDialog("Select", self, Gtk.FileChooserAction.OPEN,
                                        ("Cancel", Gtk.ResponseType.CANCEL,
                                        "Open", Gtk.ResponseType.OK))
        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            print(dialog.get_filename())
            self.imafff.set_from_file(dialog.get_filename())
        elif response == Gtk.ResponseType.CANCEL:
            print("Cancel selected")


        dialog.destroy()




window = Im()
window.connect("delete-event", Gtk.main_quit)
window.show_all();
Gtk.main()
