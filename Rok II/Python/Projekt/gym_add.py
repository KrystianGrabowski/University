import sqlite3
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk


class Gymadd(Gtk.Window):
    def __init__(self, gyms):
        Gtk.Window.__init__(self, title="New Gym")
        self.set_default_size(350, 350)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(5)
        self.grid.set_column_spacing(3)
        self.add(self.grid)
        self.gyms = gyms

        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.entry3 = Gtk.Entry()

        self.info_label = Gtk.Label("Enter necessary data: ")
        self.grid.attach(self.info_label, 5, 0, 40, 10)
        label = Gtk.Label("Name")
        self.grid.attach(label, 0, 8, 20, 10)
        self.grid.attach_next_to(self.entry1, label,
                                 Gtk.PositionType.RIGHT, 50, 10)
        label2 = Gtk.Label("Street")
        self.grid.attach(label2, 0, 16, 20, 10)
        self.grid.attach_next_to(self.entry2, label2,
                                 Gtk.PositionType.RIGHT, 50, 10)
        label3 = Gtk.Label("Number")
        self.grid.attach(label3, 0, 24, 20, 10)
        self.grid.attach_next_to(self.entry3, label3,
                                 Gtk.PositionType.RIGHT, 50, 10)

        self.add = Gtk.Button(label="Add gym")
        self.add.connect("clicked", self.add_m)
        self.grid.attach_next_to(self.add, self.entry3,
                                 Gtk.PositionType.BOTTOM, 45, 16)

        self.error_label = Gtk.Label()
        self.grid.attach(self.error_label, 30, 50, 30, 10)

    def add_m(self, widget):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        gym_name = self.entry1.get_text()
        gym_street = self.entry2.get_text()
        street_nr = self.entry3.get_text()
        if gym_name == "" or gym_street == "" or street_nr == "":
            self.error_label.set_label("Fill in the blanks!")
        elif gym_name in self.gyms:
            self.error_label.set_label("Gym already exists")
        else:
            self.cur.execute('INSERT INTO gym(name, street, nr) VALUES(?,?,?)',
                             (gym_name, gym_street, street_nr))
            self.error_label.set_label("Gym added")
            self.gyms.append(gym_name)
        self.c.commit()
        self.show_all()
