require_relative "L6Z3.rb"

def main
    my_db_open
    while true
    puts "---------------------"
    puts "1.Dodaj kontakt"
    puts "2.Wypisz"
    puts "3.Wyszukaj"
    puts "4.Wyszukaj(email)"
    puts "5.Wyszukaj(nick)"
    puts "6.Usuń"
    puts "7.Zmień email"
    puts "8.Wyjdz"
    puts "---------------------"

    choice = gets.chomp
    system "clear"
    case choice
        when '1'
            print "Imie: "
            name  = gets.chomp
            print "Nick: "
            nick  = gets.chomp
            print "Email: "
            email  = gets.chomp
            print "Numer Telefonu: "
            tel  = gets.chomp
            my_db_add(name, nick, email, tel)
        when '2'
            my_db_all
        when '3'
            print "Imie: "
            name  = gets.chomp
            my_db_find(name)
        when '4'
            print "Email: "
            email = gets.chomp
            my_db_find_email(email)
        when '5'
            print "Nick: "
            nick = gets.chomp
            my_db_find_nick(nick)
        when '6'
            print "Imie: "
            name  = gets.chomp
            my_db_delete(name)
        when '7'
            print "Imie: "
            name  = gets.chomp
            print "Email: "
            email = gets.chomp
            my_db_change_email(name, email)
        when '8'
            break

    end
    gets
    system "clear"
    end

end

main