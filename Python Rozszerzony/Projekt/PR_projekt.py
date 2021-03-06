from customer_add import *
from gym_add import *
import sqlite3
import re
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk


class My_Gyms(Gtk.Window):
    """
    Klasa umożliwiająca zarządzanie siecią siłowni
    """
    def __init__(self):
        Gtk.Window.__init__(self, title="Gym")

        self.customers = []
        self.gyms = []

        self.set_default_size(1000, 600)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(10)
        self.grid.set_column_spacing(10)
        self.add(self.grid)
        self.filter_gym = None
        self.filter_cus = None

        self.headerbar = Gtk.HeaderBar()
        self.headerbar.set_show_close_button(True)
        self.set_titlebar(self.headerbar)

        button_del = Gtk.Button(label="Delete")
        button_del.connect("clicked", self.delete_customer)
        self.headerbar.pack_end(button_del)

        self.search_entry2 = Gtk.Entry()
        self.search_entry2.connect("changed", self.search)
        self.headerbar.pack_end(self.search_entry2)

        buttonadd_c = Gtk.Button(label="+Customer")
        buttonadd_c.connect("clicked", self.new_customer)
        self.headerbar.pack_end(buttonadd_c)

        buttonadd_g = Gtk.Button(label="+Gym")
        buttonadd_g.connect("clicked", self.new_gym)
        self.headerbar.pack_start(buttonadd_g)

        self.search_entry = Gtk.Entry()
        self.search_entry.connect("changed", self.search)
        self.headerbar.pack_start(self.search_entry)

        self.load_gyms()
        self.load_customers()
        self.load_tree()

    def load_gyms(self):
        """
        Wczytywanie listy siłowni z bazy danych
        """
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.cur.execute("""CREATE TABLE IF NOT EXISTS gym(
                            name TEXT,
                            street TEXT,
                            nr INTEGER)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS customer(
                            fname TEXT,
                            sname TEXT,
                            id TEXT,
                            name TEXT,
                            FOREIGN KEY(name) REFERENCES gym(name))""")

        self.c.commit()
        self.cur.execute('SELECT * FROM gym')
        gyms_ = self.cur.fetchall()
        for gym_ in gyms_:
            if (gym_['name']) not in self.gyms:
                self.gyms.append(gym_['name'])

    def load_customers(self):
        """
        Wczytywanie listy klientów z bazy danych
        """
        self.cur.execute('SELECT * FROM customer')
        customers_ = self.cur.fetchall()
        for c_ in customers_:
            i = (c_['fname'], c_['sname'], c_['id'], c_['name'])
            if (i) not in self.customers:
                self.customers.append(i)

    def load_tree(self):
        """
        Stworzenie listy klientów w TreeView
        """
        self.customer_list = Gtk.ListStore(str, str, str, str)
        for customer_ in self.customers:
            if list(customer_) not in self.customer_list:
                self.customer_list.append(list(customer_))
        self.custgym_filter = self.customer_list.filter_new()
        self.custgym_filter.set_visible_func(self.custgym_filter_func)

        self.treeview = Gtk.TreeView.new_with_model(self.custgym_filter)
        for i, col_tit in enumerate(["First name", "Last name", "ID", "Gym"]):
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn(col_tit, renderer, text=i)
            self.treeview.append_column(column)

        self.scrollable_treelist = Gtk.ScrolledWindow()
        self.scrollable_treelist.set_vexpand(True)
        self.grid.attach(self.scrollable_treelist, 0, 0, 100, 20)
        self.scrollable_treelist.add(self.treeview)
        self.show_all()

    def delete_customer(self, widget):
        """
        Usuwanie klienita
        """
        selection = self.treeview.get_selection()
        model, path = selection.get_selected_rows()
        itr = self.customer_list.get_iter(path)
        modeltree = model.get_model()

        del_id = self.customer_list[itr][2]

        self.customer_list.remove(itr)
        self.cur.execute('DELETE FROM customer WHERE id=? ', (del_id,))
        self.c.commit()
        for c in self.customers:
            if c[2] == del_id:
                self.customers.remove(c)

    def new_customer(self, widget):
        """
        Dodawanie klienita
        """
        window2 = Custadd(self.gyms)
        window2.show_all()
        window2.connect("delete-event", self.reload)
        self.show_all()

    def new_gym(self, widget):
        """
        Dodawanie siłowni
        """
        window3 = Gymadd(self.gyms)
        window3.show_all()
        window3.connect("delete-event", self.reload_gyms)
        self.show_all()

    def reload_gyms(self, arg1, arg2):
        """
        Ponowne wczytanie siłowni
        """
        self.load_gyms()

    def reload(self, arg1, arg2):
        """
        Ponowne wczytanie całego interfejsu
        """
        self.load_gyms()
        self.load_customers()
        self.load_tree()

    def custgym_filter_func(self, model, iter, data):
        """
        Filtruje klientów według podanych parametrów

        @param iter: indeks klienita
        @param model: dane o kliencie ("wiersz")

        @return True jeśli klient "pasuje" do wpisanych filtrów
                False wpp.
        """
        if self.filter_gym is None and self.filter_cus is None:
            return True
        else:
            if self.filter_gym is not None and self.filter_cus is None:
                return re.match(self.filter_gym, model[iter][3], re.IGNORECASE)
            elif self.filter_gym is None and self.filter_cus is not None:
                return re.match(self.filter_cus, model[iter][2], re.IGNORECASE)
            else:
                a = re.match(self.filter_cus, model[iter][2], re.IGNORECASE)
                b = re.match(self.filter_gym, model[iter][3], re.IGNORECASE)
                c = a and b
                return c
        return False

    def search(self, widget):
        """
        Ustawia filtry do wyszukiwania klientów (nazwa siłowni oraz pesel)
        """
        if self.search_entry.get_text() == "":
            self.filter_gym = None
        else:
            self.filter_gym = self.search_entry.get_text()

        if self.search_entry2.get_text() == "":
            self.filter_cus = None
        else:
            self.filter_cus = self.search_entry2.get_text()
        self.load_tree()
