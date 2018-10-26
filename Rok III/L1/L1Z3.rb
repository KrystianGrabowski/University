#!/usr/bin/ruby

require_relative "numbers"

def wielkaliczba(x)
    num = x.to_s.split("")
    (0..num.length-1).each {|i| num[i] = $cyfry[num[i].to_i].split("\n")}
    for i in 1..5
        for j in 0..num.length-1
            print num[j][i] + ' ' * (6 - num[j][i].length) 
        end
        puts
    end
end

wielkaliczba(123456)
