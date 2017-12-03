import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

import sqlite3


class Music(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title = "Music")

        self.art = []
        self.rec = []
        self.tra = []

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

    def load_artists(self):
        self.c = sqlite3.connect('base.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.cur.execute("DROP TABLE IF EXISTS artysta")

        self.cur.execute("""
            CREATE TABLE artysta (
                id TEXT PRIMARY KEY,
                nazwa TEXT
            )""")

        self.cur.execute("""
            DROP TABLE IF EXISTS album
            """)
        self.cur.execute("""
            CREATE TABLE album (
            id TEXT PRIMARY KEY,
            nazwa TEXT ,
            art TEXT,
            FOREIGN KEY(art) REFERENCES artysta(nazwa)
            )""")

        self.c.commit()
        self.cur.execute('INSERT INTO artysta(nazwa) VALUES(?)', ("Slayer",))
        self.cur.execute('INSERT INTO artysta(nazwa) VALUES(?)', ("Motor",))
        self.cur.execute('INSERT INTO artysta(nazwa) VALUES(?)', ("Pantera",))
        self.c.commit()
        self.cur.execute('SELECT * FROM artysta')
        artysci = self.cur.fetchall()

        for artysta in artysci:
            print(artysta['nazwa'])
            b = Gtk.Button(label = artysta['nazwa'])
            b.connect("clicked", self.load_albums)
            self.art.append(b)

        for i in (self.art):
            self.artists.pack_start(i, True, True, 0)
        self.show_all()

    def load_albums(self, widget):
        print(widget.get_label())



window = Music()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
