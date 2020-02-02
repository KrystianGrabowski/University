def rozklad(n)
    hash = Hash.new(0)
    nr = n
    i = 2
    while (nr > 1)
        if (nr % i == 0)
            hash[i] += 1
            nr = nr/i
        else
            i += 1
        end
    end
    hash.to_a
end


def suma_dzielników(n)
    sum = 0
    for i in 1..n/2
        sum += i if (n%i == 0)
    end
    sum
end

def zaprzyjaznione(n)
    arr = []
    for i in 2..n
        sum = suma_dzielników(i)
        if (sum > i and sum <= n and suma_dzielników(sum) == i)
            arr << [i, sum]
        end
    end
    arr  
end



=begin
print("#{rozklad(1025)}\n")
print("#{rozklad(756)}\n")
print("#{rozklad(90)}\n")
print("#{rozklad(1365)}\n")
=end
print(zaprzyjaznione(50000))