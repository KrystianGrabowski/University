require 'set'

class Notebook
    def initialize
        @list = Array.new
        @groups = Set.new
    end

    def add(name, number, groups)
        if number.to_s.length != 0
            @list << [name, number.to_s, groups]
            @groups.merge(groups)
        end
    end
    
    def search_all
        @list
    end

    def search_name(name)
        @list.select{|n, _, _| n.downcase == name.downcase}
    end

    def search_number(number)
        @list.select{|_, nr, _| nr == number}
    end

    def find_groups
        @groups.to_a
    end

    def search_group(group)
        @list.select{|_, _, gr| gr.include?(group)}
    end  
end

def note
    ntb = Notebook.new
    while true
        puts %Q/Interaktywny notatnik/
        puts "1.Dodaj"
        puts "2.Wyszukaj(imię)"
        puts "3.Wszystkie grupy"
        puts "4.Wyszukaj(grupa)"
        puts "5.Wyszukaj(numer)"
        puts "6.Wszystkie kontakty"
        print "Podaj Liczbę:"
        choice = gets.chomp
        result = Array.new
        case choice.to_i
            when 1
                print "Podaj imię: "
                name = gets.chomp
                print "Podaj numer: "
                number = gets.chomp
                print "Podaj grupy: "
                groups = gets.split(" ")
                ntb.add(name, number, groups)
                print "Dodano kontakt"
            when 2
                print "Podaj imię: "
                name = gets.chomp
                ntb.search_name(name).each{|n, nr, gr| print "#{n}, #{nr}, #{gr}\n"}
            when 3
                ntb.find_groups.each{|gr| print "#{gr}\n"}
            when 4
                print "Podaj nazwę grupy: "
                group = gets.chomp
                ntb.search_group(group).each{|n, nr, gr| print "#{n}, #{nr}, #{gr}\n"}
            when 5
                print "Podaj numer telefonu: "
                number = gets.chomp
                ntb.search_number(number.to_s).each{|n, nr, gr| print "#{n}, #{nr}, #{gr}\n"}
            when 6
                ntb.search_all.each{|n, nr, gr| print "#{n}, #{nr}, #{gr}\n"}
            else
                puts "Zły zakres!"
        end
        gets
        puts `clear`
    end
end

note