#!/usr/bin/ruby

#L1Z2
def pascal(n)
    for i in 0..n-1
        (pascal_array ||= []) << 1
        (i-1).downto(1).each {|j| pascal_array[j] = pascal_array[j-1] + pascal_array[j]}
        pascal_array.each {|el| print "%d " % el}
        print "\n"
    end

end

pascal(9)
































=begin
def pascal(n)
    tab1 = [1]
    tab2 = [1]
    print "#{tab1}\n"
    for i in 0..n-1
        tab2.append(1)
        for j in 1..i
            tab2[j] = tab1[j-1] + tab1[j]
        end
        tab1 = tab2.dup
        print "#{tab2}\n"
    end

end
=end
