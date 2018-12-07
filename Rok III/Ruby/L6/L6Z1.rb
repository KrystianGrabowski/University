require 'dbm'
require 'date'
require 'time'

def my_db_open
    @db = DBM.open('z1', 0666, DBM::WRCREAT) 
end

def my_db_add_long(name, date1, date2, reminder)
    @db[name] = "#{date1}|#{date2}|#{reminder}"
    puts "> Dodano!"
end

def my_db_add_short(name, date1, reminder)
    @db[name] = "#{date1}|#{reminder}"
    puts "> Dodano!"
end

def my_db_delete(name)
    @db.has_key?(name)? (@db.delete(name); puts "Usunięto") : (puts "Nie znalezniono")
end

def show(k, v)
    x = v.split("|")
    if x.length == 3
        puts "> Nazwa: #{k}, rozpoczęcie: #{x[0]}, zakończenie: #{x[1]}, przypomnienie: #{x[2]}"
    else
        puts "> Nazwa: #{k}, data: #{x[0]}, przypomnienie: #{x[1]}"
    end
end

def my_db_all()
    @db.each do |k, v|
        show(k, v)
    end

end

def my_db_find(name)
    if @db.has_key?(name)
        show(name, @db[name])
    else
        puts "Nie znaleziono"
    end
end

def reminders()
    x = Time.now
    @db.each do |k, v|
        show(k, v) if Time.parse(v.split("|")[-1]) <= x
    end
end


