import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

import sqlite3

class My_Gyms(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title = "Gym")

        self.customers = []
        self.gyms = []

        self.set_default_size(800,600)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(10)
        self.grid.set_column_spacing(10)
        self.add(self.grid)



        self.headerbar = Gtk.HeaderBar()
        self.headerbar.set_show_close_button(True)
        self.headerbar.props.title = "My gym"
        self.set_titlebar(self.headerbar)

        buttonadd_c = Gtk.Button(label = "New customer")
        buttonadd_c.connect("clicked", self.new_customer)
        self.headerbar.pack_end(buttonadd_c)

        buttonadd_g = Gtk.Button(label = "New gym")
        buttonadd_g.connect("clicked", self.new_gym)
        self.headerbar.pack_start(buttonadd_g)

        button_del = Gtk.Button(label = "Delete")
        button_del.connect("clicked", self.delete_customer)
        self.headerbar.pack_end(button_del)

        buttsearch = Gtk.Button(label = "Search")
        buttsearch.connect("clicked", self.search)
        self.headerbar.pack_end(buttsearch)

        self.load_gyms()
        self.load_customers()
        self.load_tree()



    def load_gyms(self):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.cur.execute("CREATE TABLE IF NOT EXISTS gym(name TEXT, street TEXT, nr INTEGER)")
        self.cur.execute("CREATE TABLE IF NOT EXISTS customer(fname TEXT, sname TEXT, id TEXT , name TEXT, FOREIGN KEY(name) REFERENCES gym(name))")

        self.c.commit()
        self.cur.execute('SELECT * FROM gym')
        gyms_ = self.cur.fetchall()
        gyms = []
        for gym_ in gyms_:
            self.gyms.append(gym_['name'])


    def load_customers(self):
        self.cur.execute('SELECT * FROM customer')
        customers_ = self.cur.fetchall()
        customers = []
        for customer_ in customers_:
            self.customers.append((customer_['fname'], customer_['sname'], customer_['id'] , customer_['name']))

    def load_tree(self):
        self.customer_list = Gtk.ListStore(str, str, str, str)
        for customer_ in self.customers:
            if list(customer_) not in self.customer_list:
                self.customer_list.append(list(customer_))
        self.language_filter = self.customer_list.filter_new()

        self.treeview = Gtk.TreeView.new_with_model(self.language_filter)
        for i, colum_title in enumerate(["First name", "Last name", "ID", "Gym"]):
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn(colum_title, renderer, text=i)

            self.treeview.append_column(column)

        self.scrollable_treelist = Gtk.ScrolledWindow()
        self.scrollable_treelist.set_vexpand(True)
        self.grid.attach(self.scrollable_treelist,0,0,100,20)
        self.scrollable_treelist.add(self.treeview)
        self.show_all()


    def delete_customer(self, widget):
         selection = self.treeview.get_selection()
         model, path = selection.get_selected_rows()
         itr = self.customer_list.get_iter(path)
         modeltree = model.get_model()
         print(modeltree)
         print(model.get_string_from_iter(itr))
         #self.customer_list.remove(itr)


    def new_customer(self, widget):
        window2 = Custadd(self.gyms)
        window2.show_all()
        window2.connect("delete-event", self.reload)
        self.show_all()

    def new_gym(self, widget):
        window3 = Gymadd()
        window3.show_all()
        self.show_all()

    def reload(self,arg1,arg2):
        self.load_gyms()
        self.load_customers()
        self.load_tree()

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
        if gym_name == "" or gym_street == "" or street_nr == "" :
            self.error_label.set_label("Brak danych")
        else:
            self.cur.execute('INSERT INTO gym(name, street, nr) VALUES(?,?,?)', (gym_name, gym_street, street_nr))
            self.error_label.set_label("Udało sie")
        self.c.commit()
        self.show_all()

class Custadd(Gtk.Window):
    def __init__(self, gyms):
        Gtk.Window.__init__(self, title = "Add customer")

        self.set_default_size(300, 350)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(5)
        self.grid.set_column_spacing(3)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.entry21 = Gtk.Entry()

        self.info_label = Gtk.Label("Enter : ")
        self.grid.attach(self.info_label, 5, 0, 40, 10)
        label = Gtk.Label("Imię")
        self.grid.attach(label, 0, 8, 20, 10)
        self.grid.attach_next_to(self.entry1, label, Gtk.PositionType.RIGHT, 50, 10)
        label2 = Gtk.Label("Nazwisko")
        self.grid.attach(label2, 0, 16, 20, 10)
        self.grid.attach_next_to(self.entry2, label2, Gtk.PositionType.RIGHT, 50, 10)
        label21 = Gtk.Label("Pesel")
        self.grid.attach(label21, 0, 24, 20, 10)
        self.grid.attach_next_to(self.entry21, label21, Gtk.PositionType.RIGHT, 50, 10)
        label3 = Gtk.Label("Silownia")
        self.grid.attach(label3, 0, 32, 20, 10)

        self.combobox = Gtk.ComboBoxText()
        for gym_name in gyms:
            self.combobox.append_text(gym_name)
        self.combobox.connect("changed", self.combo_changed)
        self.grid.attach_next_to(self.combobox, label3, Gtk.PositionType.RIGHT, 50, 8)
        self.add = Gtk.Button(label = "Add customer")
        self.add.connect("clicked", self.add_m)
        self.grid.attach_next_to(self.add, self.combobox, Gtk.PositionType.BOTTOM, 45, 16)

        self.error_label = Gtk.Label()
        self.grid.attach(self.error_label, 30, 60, 30, 10 )

    def add_m(self, widget):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        cust_firstname = self.entry1.get_text()
        cust_surname = self.entry2.get_text()
        cust_id = self.entry21.get_text()
        sel_gym = self.combobox.get_active_text()


        if len(cust_id) != 11:
            self.error_label.set_label("Wrong id")
        elif sel_gym == None or cust_firstname == "" or cust_surname == "" or cust_id == "":
            self.error_label.set_label("Brak danych")
        else:
            self.cur.execute('INSERT INTO customer(fname, sname, id, name) VALUES(?,?,?,?)', (cust_firstname, cust_surname, cust_id, sel_gym))
            self.error_label.set_label("Dodano")

        self.c.commit()
        self.show_all()

    def combo_changed(self, widget):
        print("ewq")


window = My_Gyms()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
