class Wyrazenie
end

class Wartosc < Wyrazenie
    def initialize(value)
        @x = value
    end
    def to_s
        @x
    end
end

class Operacja < Wyrazenie
    attr_reader :expr1, :expr2
    def initialize(expr1, expr2)
        @expr1 = expr1
        @expr2 = expr2
    end
end

class Stala < Wartosc
    def to_s
        @x.to_s
    end
    def oblicz
        @x
    end
end

class Zmienna < Wartosc
    @@values = Hash.new
    def Zmienna.add(name, value)
        @@values[name] = value
    end
    def oblicz
        @@values[@x]
    end
end



class Dodawanie < Operacja
    def to_s
        "#{@expr1.to_s} + #{@expr2.to_s}"
    end
    def oblicz
        @expr1.oblicz + @expr2.oblicz
    end
    def uproszczenie
        return Mnozenie.new(Stala.new(2), @expr2) if @expr1.oblicz == @expr2.oblicz #x + x = 2x
    end
end

class Odejmowanie < Operacja
    def to_s
        "#{@expr1.to_s} - #{@expr2.to_s}"
    end
    def oblicz
        @expr1.oblicz - @expr2.oblicz
    end
    def uproszczenie
        return @expr1 if @expr2.oblicz == 0 #x - 0 = x
    end
end

class Mnozenie < Operacja
    def to_s
        "(#{@expr1.to_s}) * (#{@expr2.to_s})"
    end
    def oblicz
        @expr1.oblicz * @expr2.oblicz
    end
    def uproszczenie
        return Stala.new(0) if @expr1.oblicz == 0 || @expr2.oblicz == 0 #0 * x = 0
        return @expr1 if @expr2.oblicz == 1 #1 * x = x
        return @expr2 if @expr1.oblicz == 1
        return Stala.new(1) if @expr1.oblicz == @expr2.expr2.oblicz && @expr2.expr1.oblicz == 1 #x * (1/x) = 1
    end
end

class Dzielenie < Operacja
    def to_s
        "(#{@expr1.to_s}) / (#{@expr2.to_s})"
    end
    def oblicz
        @expr1.oblicz * 1.0 / @expr2.oblicz 
    end
    def uproszczenie
        return @expr1 if @expr2.oblicz == 1 #x / 1 = x
        return Stala.new(0) if @expr1.oblicz == 0 #0 / x = 0
    end
end
Zmienna.add('x', 10)
Zmienna.add('y', 3)
puts "Wyrazenie1"
wyrazenie1 = Dodawanie.new(Zmienna.new('y'), Zmienna.new('x'))
puts wyrazenie1
puts wyrazenie1.oblicz


puts "\nWyrazenie2"
wyrazenie2 = Odejmowanie.new(Stala.new(100), Zmienna.new('y'))
puts wyrazenie2
puts wyrazenie2.oblicz


puts "\nWyrazenie3"
wyrazenie3 = Mnozenie.new(Stala.new(5), Zmienna.new('y'))
puts wyrazenie3
puts wyrazenie3.oblicz


puts "\nWyrazenie4"
wyrazenie4 = Dzielenie.new(Zmienna.new('x'), Zmienna.new('y'))
puts wyrazenie4
puts wyrazenie4.oblicz

puts "\nWyrazenie5"
wyrazenie5 = Mnozenie.new(Dodawanie.new(Zmienna.new('x'), Zmienna.new('y')), Odejmowanie.new(Stala.new(66), Stala.new(55)))
puts wyrazenie5
puts wyrazenie5.oblicz


puts "\nUproszczenie1" 
upr1 = Dodawanie.new(Zmienna.new('y'), Zmienna.new('y'))
puts upr1
puts upr1.uproszczenie

puts "\nUproszczenie2" 
upr2 = Odejmowanie.new(Zmienna.new('x'), Stala.new(0))
puts upr2
puts upr2.uproszczenie

puts "\nUproszczenie3" 
upr3 = Mnozenie.new(Zmienna.new('x'), Stala.new(0))
puts upr3
puts upr3.uproszczenie

puts "\nUproszczenie4" 
upr4 = Mnozenie.new(Stala.new(1), Stala.new(666) )
puts upr4
puts upr4.uproszczenie

puts "\nUproszczenie5" 
upr5 = Mnozenie.new(Stala.new(66), Stala.new(1) )
puts upr5
puts upr5.uproszczenie

puts "\nUproszczenie6" 
upr6 = Dzielenie.new(Stala.new(66), Stala.new(1) )
puts upr6
puts upr6.uproszczenie

puts "\nUproszczenie7" 
upr7 = Dzielenie.new(Stala.new(0), Zmienna.new('x') )
puts upr7
puts upr7.uproszczenie

puts "\nUproszczenie8" 
upr8 = Mnozenie.new(Stala.new(10), Dzielenie.new(Stala.new(1), Stala.new(10)))
puts upr8
puts upr8.uproszczenie






=begin
            #return "-"+@expr2.to_s if @expr1.oblicz == 0
puts "\nUproszczenie3" 
upr3 = Odejmowanie.new(Stala.new(0), Stala.new(50) )
puts upr3
puts upr3.uproszczenie
   
=end