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

        self.set_default_size(800,600)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(10)
        self.grid.set_column_spacing(10)
        self.add(self.grid)

        self.hb = Gtk.HeaderBar()
        self.hb.set_show_close_button(True)
        self.hb.props.title = "Records"
        self.set_titlebar(self.hb)

        self.artists = Gtk.Box(spacing = 5)
        self.artists.set_size_request(50,50)
        self.grid.add(self.artists)
        self.load_artists()

        self.albums = Gtk.ListBox()
        self.grid.attach_next_to(self.albums, self.artists, Gtk.PositionType.BOTTOM,40,50)

        self.tracks = Gtk.ListBox()
        self.grid.attach_next_to(self.tracks, self.albums, Gtk.PositionType.RIGHT, 40,50)


        buttadd = Gtk.Button(label = "+")
        buttadd.connect("clicked", self.newcd)
        self.hb.pack_end(buttadd)

        buttdel = Gtk.Button(label = "-")
        buttdel.connect("clicked", self.delete)
        self.hb.pack_end(buttdel)

        buttupdate = Gtk.Button(label = "Update")
        buttupdate.connect("clicked", self.update)
        self.hb.pack_end(buttupdate)

        buttrent = Gtk.Button(label = "Rent")
        buttrent.connect("clicked", self.rent)
        self.hb.pack_end(buttrent)

        buttsearch = Gtk.Button(label = "Search")
        buttsearch.connect("clicked", self.search)
        self.hb.pack_end(buttsearch)

        self.entrysearch = Gtk.Entry()
        self.hb.pack_end(self.entrysearch)

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
        window2 = CDadd()
        window2.show_all()
        self.show_all()

    def delete(self, widget):
        window3 = CDdelete()
        window3.show_all()
        self.show_all()

    def update(self, widget):
        window4 = CDupdate()
        window4.show_all()
        self.show_all()

    def rent(self, widget):
        window4 = CDrent()
        window4.show_all()
        self.show_all()

    def search(self, widget):
        self.albums = Gtk.ListBox()
        self.grid.attach_next_to(self.albums, self.artists, Gtk.PositionType.BOTTOM,30,50)
        self.tracks = Gtk.ListBox()
        self.grid.attach_next_to(self.tracks, self.albums, Gtk.PositionType.RIGHT, 50,50)
        self.cur.execute('SELECT * FROM album WHERE nazwa = ?', (self.entrysearch.get_text(), ))
        albums_list = self.cur.fetchall()
        for album_ in albums_list:
            b2 = Gtk.Button(label = album_['nazwa'])
            b2.connect("clicked", self.load_tracks)
            self.albums.add(b2)
        self.show_all()

class CDadd(Gtk.Window):
    def __init__(self):

        Gtk.Window.__init__(self, title = "Add")

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
        self.cur.execute('SELECT * FROM artysta WHERE nazwa = ? ', (addArtysta, ))
        a = self.cur.fetchall()
        if len(a) == 0:
            self.cur.execute('INSERT INTO artysta(nazwa) VALUES(?)', (addArtysta,))
        self.cur.execute('INSERT INTO album(nazwa, art) VALUES(?, ?)', (addAlbum, addArtysta,))

        addTracks = self.entry3.get_text()
        addTracks_list = addTracks.split("-")
        for i in addTracks_list:
            self.cur.execute('INSERT INTO track(tr, nazwa, art) VALUES(?, ?, ?)', (i, addAlbum, addArtysta,))
        self.c.commit()

class CDdelete(Gtk.Window):
    def __init__(self):

        Gtk.Window.__init__(self, title = "Delete")

        self.set_default_size(100,100)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(2)
        self.grid.set_column_spacing(2)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()

        self.grid.add(self.entry1)

        addbut = Gtk.Button(label = "Delete")
        addbut.connect("clicked", self.del_)
        self.grid.attach_next_to(addbut, self.entry1, Gtk.PositionType.BOTTOM, 20, 20)

    def del_(self, widget):

        self.c = sqlite3.connect('base.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        delAlbum = self.entry1.get_text()
        self.cur.execute('DELETE FROM track WHERE nazwa=?', (delAlbum,))
        self.cur.execute('DELETE FROM album WHERE nazwa=?', (delAlbum,))
        self.c.commit()

class CDupdate(Gtk.Window):
    def __init__(self):

        Gtk.Window.__init__(self, title = "Delete")

        self.set_default_size(200,200)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(2)
        self.grid.set_column_spacing(2)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()
        self.entry2 = Gtk.Entry()
        self.grid.attach(self.entry1,0,0,20,20)
        self.grid.attach_next_to(self.entry2,self.entry1, Gtk.PositionType.BOTTOM,20,20)

        addbut = Gtk.Button(label = "Update")
        addbut.connect("clicked", self.update_)
        self.grid.attach_next_to(addbut, self.entry2, Gtk.PositionType.BOTTOM, 20, 20)

    def update_(self, widget):

        self.c = sqlite3.connect('base.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        updateAlbum = self.entry1.get_text()
        updateAlbumT = self.entry2.get_text()
        self.cur.execute('UPDATE track SET nazwa=? WHERE nazwa=?', (updateAlbumT, updateAlbum,))
        self.cur.execute('UPDATE album SET nazwa=? WHERE nazwa=?', (updateAlbumT, updateAlbum,))
        self.c.commit()

class CDrent(Gtk.Window):
    def __init__(self):

        Gtk.Window.__init__(self, title = "Rent")

        self.set_default_size(200,200)
        self.grid = Gtk.Grid()
        self.grid.set_row_spacing(2)
        self.grid.set_column_spacing(2)
        self.add(self.grid)

        self.entry1 = Gtk.Entry()
        self.grid.attach(self.entry1,0,0,20,20)

        addbut = Gtk.Button(label = "Update")
        addbut.connect("clicked", self.rent_)
        self.grid.attach_next_to(addbut, self.entry1, Gtk.PositionType.BOTTOM, 20, 20)

    def rent_(self, widget):

        self.c = sqlite3.connect('base.db')
        self.c.row_factory = sqlite3.Row
        self.cur = self.c.cursor()

        updateAlbum = self.entry1.get_text()
        updateAlbumT = updateAlbum + "(wypozyczone)"
        self.cur.execute('UPDATE track SET nazwa=? WHERE nazwa=?', (updateAlbumT, updateAlbum,))
        self.cur.execute('UPDATE album SET nazwa=? WHERE nazwa=?', (updateAlbumT, updateAlbum,))
        self.c.commit()

window = Music()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
