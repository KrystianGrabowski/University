require_relative "L6Z1.rb"

def main
    my_db_open
    while true
    puts "---------------------"
    puts "1.Nowe do zrobienia"
    puts "2.Nowe spotkanie"
    puts "3.Wyświetl"
    puts "4.Wyświetl zadanie"
    puts "5.Usuń"
    puts "6.Aktualne przypomnienia"
    puts "7.Wyjdz"
    puts "---------------------"

    choice = gets.chomp
    system "clear"
    case choice
        when '1'
            print "Nazwa: "
            name  = gets.chomp
            print "Data1: "
            date1  = gets.chomp
            print "Przypomnienie: "
            reminder  = gets.chomp
            my_db_add_short(name, date1, reminder)
        when '2'
            print "Nazwa: "
            name  = gets.chomp
            print "Data1: "
            date1  = gets.chomp
            print "Data2: " 
            date2  = gets.chomp
            print "Przypomnienie: "
            reminder  = gets.chomp
            my_db_add_long(name, date1, date2, reminder)
        when '3'
            my_db_all
        when '4'
            print "Nazwa: "
            name  = gets.chomp
            my_db_find(name)
        when '5'
            print "Nazwa: "
            name  = gets.chomp
            my_db_delete(name)

        when '6'
            reminders
        when '7'
            break

    end
    gets
    system "clear"
    end

end

main
