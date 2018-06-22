
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
	
	def wykres(x1,x2,y1,y2)
		d = 100
		skokx = (x2-x1)/d
		skoky = (y1-y2)/(d/2)
		wspy = y1
		wspx = x1
		
		for z in 1..d+2
			print '-'
		end
		for i in 1..d/2
			puts
			wspy = wspy - skoky
			y = wspy.round(2)
			print'|'
			for i in 1..d
				if value(wspx).round(2) >= wspy
					print ' '
				else
					print'*'
				end
				wspx = wspx + skokx
				wspx = wspx.to_f.round(3)
				
				
			end
			print '|'
			wspx = x1
			
		end
		puts
		for o in 1..d+2
			print '-'
		end

	end
	
end


f = lambda{|x| x }
x = Funkcja.new(f)
puts "Przyblizony wykres funkcji: "
x.wykres(-5.0, 5.0, 5.0, -5.0)