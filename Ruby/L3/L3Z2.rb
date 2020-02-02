def pierwsza(n)
    (2..n).select {|it| (2..Math.sqrt(it)).each {|div| break if it%div == 0}}
end

def doskonale(n)
    (2..n).select {|it| ((1..it/2).inject(0) {|sum, x| it%x == 0? sum+x : sum }) == it}
end


print(doskonale(10000))
puts
print(pierwsza(100))


=begin

def doskonaletest(n)
    arr = []
    for i in (2..n)
        sum = 0
        for j in 1..i/2
            if i % j == 0
                sum += j
            end
        end
        arr << i if sum == i
    end
    arr
end

def pierwszatest(n)
    arr = []
    for i in 2..n
        primes = true
        for j in 2..Math.sqrt(i)
            if i%j == 0
                primes = false
            end
        end
        arr << i if primes
    end
    arr
end
start = Time.now

finish = Time.now
puts(finish - start)
start = Time.now
print(doskonaletest(20000))
finish = Time.now
puts(finish - start)


start = Time.now
pierwsza(500000)
finish = Time.now
puts(finish - start)
start = Time.now
pierwszatest(500000)
finish = Time.now
puts(finish - start)
puts (pierwsza(100000) == pierwszatest(100000))
=end




