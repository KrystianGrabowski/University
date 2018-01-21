import sqlite3
from threading import Thread, Lock
import queue as queue
import gi
from gi.repository import Gtk
gi.require_version('Gtk', '3.0')


class Custadd(Gtk.Window):
    def __init__(self, gyms):
        Gtk.Window.__init__(self, title="Add customer")

        self.set_default_size(350, 350)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(5)
        self.grid.set_column_spacing(3)
        self.add(self.grid)

        self.gyms_add = gyms
        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.entry21 = Gtk.Entry()

        self.info_label = Gtk.Label("Enter necessary data: ")
        self.grid.attach(self.info_label, 5, 0, 40, 10)
        label = Gtk.Label("FName")
        self.grid.attach(label, 0, 8, 20, 10)
        self.grid.attach_next_to(self.entry1, label, Gtk.PositionType.RIGHT, 50, 10)
        label2 = Gtk.Label("Sname")
        self.grid.attach(label2, 0, 16, 20, 10)
        self.grid.attach_next_to(self.entry2, label2, Gtk.PositionType.RIGHT, 50, 10)
        label21 = Gtk.Label("ID")
        self.grid.attach(label21, 0, 24, 20, 10)
        self.grid.attach_next_to(self.entry21, label21, Gtk.PositionType.RIGHT, 50, 10)
        label3 = Gtk.Label("Gym")
        self.grid.attach(label3, 0, 32, 20, 10)

        self.combobox = Gtk.ComboBoxText()
        for gym_name in self.gyms_add:
            self.combobox.append_text(gym_name)
        self.grid.attach_next_to(self.combobox, label3, Gtk.PositionType.RIGHT, 50, 8)
        self.add = Gtk.Button(label = "Add customer")
        self.add.connect("clicked", self.add_m)
        self.grid.attach_next_to(self.add, self.combobox, Gtk.PositionType.BOTTOM, 45, 16)

        self.error_label = Gtk.Label()
        self.grid.attach(self.error_label, 30, 60, 30, 10 )

    def check(self, cust, cust_id):
        lck = Lock()
        for c in cust:
            if c['id'] == cust_id:
                lck.acquire()
                self.my_set.add(c['name'])
                lck.release()



    def add_m(self, widget):
        self.c = sqlite3.connect('gym.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.my_set = set()
        self.is_ok = True

        cust_firstname = self.entry1.get_text()
        cust_surname = self.entry2.get_text()
        cust_id = self.entry21.get_text()
        sel_gym = self.combobox.get_active_text()


        if sel_gym == None or cust_firstname == "" or cust_surname == "" or cust_id == "":
            self.error_label.set_label("Fill in the blanks!")
        elif len(cust_id) != 11:
            self.error_label.set_label("Wrong ID")
        else:
            q = queue.Queue()
            for gym in self.gyms_add:
                self.cur.execute('SELECT * FROM customer WHERE name = ?', (gym,))
                cust = self.cur.fetchall()
                thread = Thread(target = self.check, args = (cust, cust_id))
                thread.start()
                q.put(thread)
            while(not q.empty()):
                q.get().join()

            if len(self.my_set) > 3 :
                self.error_label.set_label("Limit of gyms exceeded")
                self.is_ok = False
            else:
                while len(self.my_set):
                    if self.my_set.pop() == sel_gym:
                        self.error_label.set_label("Customer already exists")
                        self.is_ok = False

            if self.is_ok:
                self.cur.execute('INSERT INTO customer(fname, sname, id, name) VALUES(?,?,?,?)', (cust_firstname, cust_surname, cust_id, sel_gym))
                self.error_label.set_label("Customer added")

        self.c.commit()
        self.show_all()
