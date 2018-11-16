klucz = 
{
'a' => 'b', 
'b' => 'r', 
'r' => 'y', 
'y' => 'u', 
'u' => 'a'
}

class Jawna
	def initialize(napis)
		@napis = napis
	end
	
	def to_s 
		@napis
	end
	
	def zaszyfruj(klucz)

		nw = ""
		lg = @napis.length
		i = 0
		while  i != lg	
			nw = nw + klucz[@napis[i]]
			i = i + 1 
			
		end
		return Zaszyfrowane.new(nw)
			

	end
end

class Zaszyfrowane
	def initialize(napis)
		@napis = napis
	end
	
	def to_s 
		@napis
	end
	
	def odszyfruj(klucz)
		nw = ""
		lg = @napis.length
		i = 0
		while  i != lg	
			nw = nw + klucz.key(@napis[i])
			i = i + 1 
			
		end
		return Jawna.new(nw)
			

	end
	
end

x = Jawna.new("ruby")
puts x.zaszyfruj(klucz)
puts x.to_s
puts

y = Zaszyfrowane.new("yaru")
puts y.odszyfruj(klucz)
puts y.to_s