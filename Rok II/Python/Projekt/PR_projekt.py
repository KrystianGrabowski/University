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


        buttonadd_c = Gtk.Button(label = "New customer")
        buttonadd_c.connect("clicked", self.new_customer)
        self.headerbar.pack_end(buttonadd_c)

        buttonadd_g = Gtk.Button(label = "New gym")
        buttonadd_g.connect("clicked", self.new_gym)
        self.headerbar.pack_start(buttonadd_g)

        buttsearch = Gtk.Button(label = "Search")
        buttsearch.connect("clicked", self.search)
        self.headerbar.pack_end(buttsearch)

        self.load_gyms();



    def load_gyms(self):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.cur.execute("CREATE TABLE IF NOT EXISTS gym(name TEXT, street TEXT, nr INTEGER)")
        self.cur.execute("CREATE TABLE IF NOT EXISTS customer(fname TEXT, sname TEXT, name TEXT, FOREIGN KEY(name) REFERENCES gym(name))")

        self.c.commit()
        self.cur.execute('SELECT * FROM gym')
        gyms_ = self.cur.fetchall()

        for gym_ in gyms_:
            b = Gtk.Button(label = gym_['name'])
            b.connect("clicked", self.load_customers)
            self.gyms.append(b)

        for i in self.gyms:
            self.gyms_list.add(i)
        self.show_all()


    def load_customers(self, widget):

        self.customers_list.gtk_container_remove( self.customers_list)
        self.cur.execute('SELECT * FROM customer WHERE name = ?', (widget.get_label(), ))
        customers_ = self.cur.fetchall()
        for customer_ in customers_:
            print("DSADA")
            b2 = Gtk.Label(customer_['fname'] + " " + customer_['sname'])
            self.customers_list.add(b2)

        #self.customers_list.show_all()
        '''for j in self.customers:
            self.customers_list.add(j)

        #self.show_all()
        '''
    def cust_info(self, widget):
        print("info")

    def new_customer(self, widget):
        window2 = Custadd(self.gyms)
        window2.show_all()
        self.show_all()

    def new_gym(self, widget):
        window3 = Gymadd()
        window3.show_all()
        self.show_all()

    def search(self, widget):
        print("search")

class Gymadd(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title = "New Gym")
        self.set_default_size(350, 350)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(5)
        self.grid.set_column_spacing(3)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.entry3 = Gtk.Entry()

        self.info_label = Gtk.Label("Podaj dane o siłowni: ")
        self.grid.attach(self.info_label, 5, 0, 40, 10)
        label = Gtk.Label("Name")
        self.grid.attach(label, 0, 8, 20, 10)
        self.grid.attach_next_to(self.entry1, label, Gtk.PositionType.RIGHT, 50, 10)
        label2 = Gtk.Label("Street")
        self.grid.attach(label2, 0, 16, 20, 10)
        self.grid.attach_next_to(self.entry2, label2, Gtk.PositionType.RIGHT, 50, 10)
        label3 = Gtk.Label("Number")
        self.grid.attach(label3, 0, 24, 20, 10)
        self.grid.attach_next_to(self.entry3, label3, Gtk.PositionType.RIGHT, 50, 10)

        self.add = Gtk.Button(label = "Add gym")
        self.add.connect("clicked", self.add_m)
        self.grid.attach_next_to(self.add, self.entry3, Gtk.PositionType.BOTTOM, 45, 16)

        self.error_label = Gtk.Label()
        self.grid.attach(self.error_label, 30, 50, 30, 10 )

    def add_m(self, widget):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        gym_name = self.entry1.get_text()
        gym_street = self.entry2.get_text()
        street_nr = self.entry3.get_text()
        if gym_name == "" or gym_street == "" or street_nr == "":
            self.error_label.set_label("Brak danych")
        else:
            self.cur.execute('INSERT INTO gym(name, street, nr) VALUES(?,?,?)', (gym_name, gym_street, street_nr))
            self.error_label.set_label("Udało sie")
        self.c.commit()
        self.show_all()

class Custadd(Gtk.Window):
    def __init__(self, gyms):
        Gtk.Window.__init__(self, title = "Add customer")

        self.set_default_size(350, 350)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(5)
        self.grid.set_column_spacing(3)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()

        self.info_label = Gtk.Label("Enter : ")
        self.grid.attach(self.info_label, 5, 0, 40, 10)
        label = Gtk.Label("Imię")
        self.grid.attach(label, 0, 8, 20, 10)
        self.grid.attach_next_to(self.entry1, label, Gtk.PositionType.RIGHT, 50, 10)
        label2 = Gtk.Label("Nazwisko")
        self.grid.attach(label2, 0, 16, 20, 10)
        self.grid.attach_next_to(self.entry2, label2, Gtk.PositionType.RIGHT, 50, 10)
        label3 = Gtk.Label("Silownia")
        self.grid.attach(label3, 0, 24, 20, 10)

        self.combobox = Gtk.ComboBoxText()
        for gym_name in gyms:
            self.combobox.append_text(gym_name.get_label())
        self.combobox.connect("changed", self.combo_changed)
        self.grid.attach_next_to(self.combobox, label3, Gtk.PositionType.RIGHT, 50, 8)
        self.add = Gtk.Button(label = "Add customer")
        self.add.connect("clicked", self.add_m)
        self.grid.attach_next_to(self.add, self.combobox, Gtk.PositionType.BOTTOM, 45, 16)

        self.error_label = Gtk.Label()
        self.grid.attach(self.error_label, 30, 50, 30, 10 )

    def add_m(self, widget):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        cust_firstname = self.entry1.get_text()
        cust_surname = self.entry2.get_text()
        sel_gym = self.combobox.get_active_text()
        if sel_gym == None or cust_firstname == "" or cust_surname == "":
            self.error_label.set_label("Brak danych")
        else:
            self.cur.execute('INSERT INTO customer(fname, sname, name) VALUES(?,?,?)', (cust_firstname, cust_surname, sel_gym))
            self.error_label.set_label("Dodano")

        self.c.commit()
        self.show_all()

    def combo_changed(self, widget):
        print("ewq")


window = My_Gyms()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
