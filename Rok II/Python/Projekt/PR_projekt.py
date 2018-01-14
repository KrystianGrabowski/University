import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

import sqlite3

class My_Gyms(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title = "Gym")

        self.gyms = []
        self.customers = []

        self.set_default_size(800,600)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(10)
        self.grid.set_column_spacing(10)
        self.add(self.grid)

        self.headerbar = Gtk.HeaderBar()
        self.headerbar.set_show_close_button(True)
        self.headerbar.props.title = "My gym"
        self.set_titlebar(self.headerbar)

        self.gyms_list = Gtk.ListBox()
        self.grid.attach(self.gyms_list,0,0,40,50)

        self.customers_list = Gtk.ListBox()
        self.grid.attach_next_to(self.customers_list, self.gyms_list,
            Gtk.PositionType.RIGHT, 40, 50)


        buttonadd = Gtk.Button(label = "+")
        buttonadd.connect("clicked", self.new_customer)
        self.headerbar.pack_end(buttonadd)

        buttsearch = Gtk.Button(label = "Search")
        buttsearch.connect("clicked", self.search)
        self.headerbar.pack_end(buttsearch)

        self.load_gyms();



    def load_gyms(self):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.cur.execute("CREATE TABLE IF NOT EXISTS gym(nazwa TEXT, ulica TEXT, numer INTEGER)")
        self.cur.execute("CREATE TABLE IF NOT EXISTS customer(imie TEXT, nazwisko TEXT, nazwa TEXT, FOREIGN KEY(nazwa) REFERENCES gym(nazwa))")

        self.c.commit()


        self.cur.execute('SELECT * FROM gym')
        gyms_ = self.cur.fetchall()

        for gym_ in gyms_:
            b = Gtk.Button(label = gym_['nazwa'])
            b.connect("clicked", self.load_customers)
            self.gyms.append(b)

        for i in self.gyms:
            self.gyms_list.add(i)
        self.show_all()


    def load_customers(self, widget):
        self.customers_list = Gtk.ListBox()
        self.grid.attach_next_to(self.customers_list, self.gyms_list,
            Gtk.PositionType.RIGHT, 40, 50)
        self.cur.execute('SELECT * FROM customer WHERE nazwa = ?', (widget.get_label(), ))
        customers_ = self.cur.fetchall()
        for customer_ in customers_:
            b2 = Gtk.Button(label = customer_['imie'] + customer_['nazwisko'])
            b2.connect("clicked", self.cust_info)
            self.customers.append(b2)

        for j in self.customers:
            self.customers_list.add(j)
        self.show_all()

    def cust_info(self, widget):
        print("info")

    def new_customer(self, widget):
        window2 = Custadd(self.gyms)
        window2.show_all()
        self.show_all()

    def search(self, widget):
        print("search")


class Custadd(Gtk.Window):
    def __init__(self, gyms):
        Gtk.Window.__init__(self, title= "Add")

        self.set_default_size(300, 300)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(5)
        self.grid.set_column_spacing(3)
        self.add(self.grid)


        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.entry3 = Gtk.Entry()

        label = Gtk.Label("Imię")
        self.grid.attach(label, 0, 0, 20, 10)
        self.grid.attach_next_to(self.entry1, label, Gtk.PositionType.RIGHT, 50, 10)
        label2 = Gtk.Label("Nazwisko")
        self.grid.attach(label2, 0, 8, 20, 10)
        self.grid.attach_next_to(self.entry2, label2, Gtk.PositionType.RIGHT, 50, 10)
        label3 = Gtk.Label("Silownia")
        self.grid.attach(label3, 0, 16, 20, 10)

        combobox = Gtk.ComboBoxText()
        for gym_name in gyms:
            combobox.append_text(gym_name.get_label())
            combobox.append_text("test1")
            combobox.append_text("test2")
        combobox.connect("changed", self.combo_changed)
        self.grid.attach_next_to(combobox, label3, Gtk.PositionType.RIGHT, 50, 8)



    def combo_changed(self, widget):
        print("ewq")


window = My_Gyms()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
