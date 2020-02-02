require 'dbm'


def my_db_open
    @db = DBM.open('z3', 0666, DBM::WRCREAT) 
end

def my_db_add(name, nick=nil, email=nil , tel=nil)
    if (email_validation(email) && phone_number_validation(tel))
        @db[name] = "#{nick}|#{email}|#{tel}"
        puts "> Dodano"
    else
        puts "> Błędne dane"
    end
end

def email_validation(email)
    /^[0-9a-zA-Z_.-]+@[0-9a-zA-Z.-]+[a-zA-Z]{2,3}$/.match(email)
end

def phone_number_validation(phn)
    /^[0-9]{9}$/.match(phn)
end


def my_db_delete(name)
    @db.has_key?(name)? (@db.delete(name); puts "> Usunięto") : (puts "> Nie znalezniono")
end

def show(k, v)
    x = v.split("|")
    puts "> Imie: #{k}, nick: #{x[0]}, e-mail: #{x[1]}, numer telefonu: #{x[2]}"
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
        puts "> Nie znaleziono"
    end
end

def my_db_find_email(email)
    @db.each do |k, v|
        show(k, v) if v.split("|")[1].downcase == email.downcase
    end
end

def my_db_find_nick(nick)
    @db.each do |k, v|
        show(k, v) if v.split("|")[0].downcase == nick.downcase
    end
end

def change(x, i, y)
    x = x.split("|")
    x[i] = y
    x.join("|")
end

def my_db_change_email(nick, email)
    if email_validation(email) and @db.has_key?(nick)
        x = change(@db[nick], 1, email)
        @db[nick] = x
        puts "> Zmieniono"
    else
        puts "> Błąd"
    end
end 



