from customer_add import *
from gym_add import *
from PR_projekt import *


window = My_Gyms()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()
