#!/usr/bin/ruby

def pierwsza(n)
    (2..Math.sqrt(n)).each {|i| return false if n%i == 0}
    true
end

def podzielniki(n)
    for j in 2..n
        if n%j == 0 and pierwsza(j)
            (tab ||= []) << j # ||= przypisanie jesli left = nil,false  || #tab << j
            n = n/j                                                        #tab.push(j)
        end
    end
    tab
end

print podzielniki(1025)
