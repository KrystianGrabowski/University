
class Funkcja 
	def initialize (r)
		@l = r
	end
	
	def value(x)
		@l.call(x)
	end
	
	def zerowe(a, b, e)
	i = a
	d = e.to_s.length
	tab = []
	while (i <= b)
		if @l.call(i).round(9) == 0
			tab = tab + [i]
		end
		i = i + e
		i = i.to_f.round(d)
	end
		return tab
	end

	def pole(a, b)
		n = 1000.0
		x = (b-a)/n
		s = 0.0
		
			for i in 1..n
				y = value(a + (x * (i-1)))
				s = s + (x * y)

			end
		return s.round(5)
	end
	
	def poch(x)
		n = 0.000000001
		a = (value(x+n) - value(x))/n
		return a.to_f.round(5)
	end	
end


f = lambda{|x| x*x*x }
x = Funkcja.new(f)

print "Wartosc w punkcie: "
puts x.value(3)

print "Wartosc pochodnej w punkcie ~ "
puts x.poch(2)

print "Pole tworzone przez wykres ~ "
puts x.pole(0, 2)

puts "Miejsca zerowe: "
puts x.zerowe(-3.0,3.0,0.001)