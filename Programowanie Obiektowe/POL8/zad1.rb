class Fixnum 
	
	def czynniki
		tab = []
		for i in (1...self+1)
			if self % i == 0
				tab = tab + [i]
			end
		end
		return tab
	end
	
	def ack(y)
		return y + 1 if self == 0
		return (self - 1).ack(1) if y == 0
		return (self - 1).ack(self.ack(y - 1))
	end
	
	def doskonala?
		w = 0
		if self != 0
			for i in (1...self/2 + 1)
				if self % i == 0 
					w = w + i
				end
			end

			return true if w == self
		end
		return false 
	
	end 
	
	def slownie
		cyfra = ["zero", "jeden", "dwa", "trzy", "cztery", "piec", "szesc", "siedem", "osiem", "dziewiec"]
		b = self
		napis = ""
		
		begin
			c = b % 10
			b = b / 10
			napis = cyfra[c] + " " + napis
		end while b!=0
		
	return napis
	end
end

puts "-------czynniki-------"
print 0.czynniki
puts
print 1.czynniki
puts
print 6.czynniki
puts
print 100.czynniki
puts
puts "-------ack-------"
puts 2.ack(1)
puts "-------doskonala-------"
puts 6.doskonala?
puts 1.doskonala?
puts 496.doskonala?
puts 495.doskonala?
puts 0.doskonala?
puts 8128.doskonala?
puts "-------slownie-------"
puts 123.slownie
puts 521.slownie
puts 0.slownie
puts 1.slownie
puts 84172641.slownie



