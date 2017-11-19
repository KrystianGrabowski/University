from html.parser import HTMLParser
import urllib.request
from urllib import parse
import re
import threading
import queue
from time import clock
class MyHTML(HTMLParser):
    def __init__(self, b_url):
        self.base_url = b_url
        self.links = []
        self.fed = []
        self.is_text = False
        super().__init__()

    def handle_starttag(self,tag,attrs):
        if tag == 'body':
            self.is_text = True

        if tag == 'a':
            for (attribute,value) in attrs:
                if attribute == 'href':
                    url = parse.urljoin(self.base_url, value)
                    if re.match("^(http|https)://",url):
                        self.links.append(url)

    def handle_endtag(self, tag):
        if tag == 'body':
            self.is_text = False

    def handle_data(self, d):
        if self.is_text:
            self.fed.append(d)

    def get_data(self):
        return ''.join(self.fed)

    def pages(self):
        return self.links

class Poszukiwacz :
    def __init__(self, cel, strona):
        self.strona = strona
        self.cel = cel
        self.liczba_wystapien = 0
        self.wyszukiwanie()

    def wyszukiwanie(self):
        with urllib.request.urlopen(self.strona) as dane:
            html = dane.read()
        self.html_p = MyHTML(self.strona)
        self.html_p.feed(str(html))
        tekst_strony = self.html_p.get_data()
        szukane = re.compile(self.cel, re.IGNORECASE)
        self.liczba_wystapien = len(re.findall(szukane, tekst_strony))

    def odnosniki(self):
        return self.html_p.pages()

    def __str__(self):
        return self.strona

Wyniki_wyszukiwania = []
przeszukane = set()
lista = []
def mini_wyszukiwarka(szukana_fraza, url, glebokosc):
    przeszukane.add(url)
    if glebokosc < 0:
        return 0
    html_chck = Poszukiwacz(szukana_fraza, url)
    if glebokosc > 0 :
        odnosniki = html_chck.odnosniki()
    else:
        odnosniki = []
    w = False
    if html_chck.liczba_wystapien != 0:
        for l in range(len(Wyniki_wyszukiwania)):
            if html_chck.liczba_wystapien > Wyniki_wyszukiwania[l].liczba_wystapien:
                Wyniki_wyszukiwania.insert(l, html_chck)
                w = True
                break
        if not w:
            Wyniki_wyszukiwania.append(html_chck)
    q = queue.Queue()
    for link in odnosniki:
        if link not in przeszukane:
            thread = threading.Thread(target = mini_wyszukiwarka, args = (szukana_fraza, link, glebokosc - 1))
            thread.start()
            q.put(thread)

    while(not q.empty()):
        q.get().join()
    return Wyniki_wyszukiwania

time1 = clock()
for i in (mini_wyszukiwarka("Python", "https://pl.python.org/docs/lib/msvcrt-console.html#l2h-4699",1)):
     print(i,i.liczba_wystapien)
print(clock() - time1)
"""
print("________________")
for i in (mini_wyszukiwarka("Python", "https://www.ii.uni.wroc.pl/~marcinm/dyd/python/",1)):
    print(i,i.liczba_wystapien)
    """
