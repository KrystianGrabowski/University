import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

import sqlite3


class Music(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title = "Music")

        self.art = []
        self.alb = []
        self.tra = []

        self.set_default_size(1024,700)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(10)
        self.grid.set_column_spacing(10)
        self.add(self.grid)

        scrolled = Gtk.ScrolledWindow()
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        #self.add(scrolled)

        self.hb = Gtk.HeaderBar()
        self.hb.set_show_close_button(True)
        self.hb.props.title = "Records"
        self.set_titlebar(self.hb)

        self.artists = Gtk.Box(spacing = 5)
        self.artists.set_size_request(150,150)
        self.grid.add(self.artists)
        self.load_artists()

        self.albums = Gtk.ListBox()
        self.grid.attach_next_to(self.albums, self.artists, Gtk.PositionType.BOTTOM,30,50)

        self.tracks = Gtk.ListBox()
        self.grid.attach_next_to(self.tracks, self.albums, Gtk.PositionType.RIGHT, 50,60)


        butadd = Gtk.Button(label = "+")
        butadd.connect("clicked", self.newcd)
        self.hb.pack_end(butadd)

    def add_(self, widget):
        addArtysta = self.entry1.get_text()
        addAlbum = self.entry2.get_text()
        addTracks = self.entry3.get_text()

        self.cur.execute('INSERT INTO artysta(nazwa) VALUES(?)', (addArtysta,))
        self.cur.execute('INSERT INTO album(nazwa, art) VALUES(?, ?)', (addAlbum, addArtysta,))
        self.cur.execute('INSERT INTO track(tr, nazwa, art) VALUES(?, ?, ?)', (addTracks, addAlbum, addTracks,))
        self.c.commit()
        self.cur.execute('SELECT * FROM artysta')
        ex = self.cur.fetchall()
        bu = Gtk.Button(label = addArtysta)
        bu.connect("clicked", self.load_albums)
        self.artists.add(bu)
        self.show_all()

    def load_artists(self):
        self.c = sqlite3.connect('base.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        self.cur.execute("CREATE TABLE IF NOT EXISTS artysta(nazwa TEXT)" )
        self.cur.execute("CREATE TABLE IF NOT EXISTS album(nazwa TEXT, art TEXT, FOREIGN KEY(art) REFERENCES artysta(nazwa))" )
        self.cur.execute("CREATE TABLE IF NOT EXISTS track(tr TEXT, nazwa TEXT, art TEXT, FOREIGN KEY(art) REFERENCES artysta(nazwa), FOREIGN KEY(nazwa) REFERENCES album(nazwa))" )

        self.c.commit()
        self.cur.execute('SELECT * FROM artysta')
        artists_list = self.cur.fetchall()

        for artist_ in artists_list:
            b = Gtk.Button(label = artist_['nazwa'])
            b.connect("clicked", self.load_albums)
            self.art.append(b)

        for i in (self.art):
            self.artists.pack_start(i, True, True, 0)
        self.show_all()

    def load_albums(self, widget):
        self.albums = Gtk.ListBox()
        self.grid.attach_next_to(self.albums, self.artists, Gtk.PositionType.BOTTOM,30,50)
        self.tracks = Gtk.ListBox()
        self.grid.attach_next_to(self.tracks, self.albums, Gtk.PositionType.RIGHT, 50,50)
        self.cur.execute('SELECT * FROM album WHERE art = ?', (widget.get_label(), ))
        albums_list = self.cur.fetchall()
        for album_ in albums_list:
            b2 = Gtk.Button(label = album_['nazwa'])
            b2.connect("clicked", self.load_tracks)
            self.albums.add(b2)
        self.show_all()

    def load_tracks(self, widget):
        self.tracks = Gtk.ListBox()
        self.grid.attach_next_to(self.tracks, self.albums, Gtk.PositionType.RIGHT, 50,50)
        self.cur.execute('SELECT * FROM track WHERE nazwa = ? ', (widget.get_label(), ))
        tracks_list = self.cur.fetchall()
        for track_ in tracks_list:
            l = Gtk.Label(track_['tr'])
            self.tracks.add(l)
        self.show_all()

    def newcd(self, widget):
        window2 = CDWin()
        window2.show_all()
        self.show_all()

class CDWin(Gtk.Window):
    def __init__(self):

        Gtk.Window.__init__(self, title = "New")

        self.set_default_size(200,300)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(2)
        self.grid.set_column_spacing(2)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.entry3 = Gtk.Entry()

        self.grid.attach(self.entry1,0,0,20,20)
        self.grid.attach_next_to(self.entry2, self.entry1, Gtk.PositionType.BOTTOM, 20, 20)
        self.grid.attach_next_to(self.entry3, self.entry2, Gtk.PositionType.BOTTOM, 20, 20)

        addbut = Gtk.Button(label = "Add")
        addbut.connect("clicked", self.add_)
        self.grid.attach_next_to(addbut, self.entry3, Gtk.PositionType.BOTTOM, 20, 20)

    def add_(self, widget):

        self.c = sqlite3.connect('base.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        addArtysta = self.entry1.get_text()
        addAlbum = self.entry2.get_text()
        addTracks = self.entry3.get_text()

        self.cur.execute('INSERT INTO artysta(nazwa) VALUES(?)', (addArtysta,))
        self.cur.execute('INSERT INTO album(nazwa, art) VALUES(?, ?)', (addAlbum, addArtysta,))
        self.cur.execute('INSERT INTO track(tr, nazwa, art) VALUES(?, ?, ?)', (addTracks, addAlbum, addTracks,))
        self.c.commit()
        self.show_all()




window = Music()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
