def calka(a,b,&blok)
    (a+0.5).step(to: b, by: 0.5).inject(0) {|sum, x|  sum + (blok.call(x) * 0.5)}
end

def wykres(a, b, &blok)
    20.downto(-20) {|y| ((a).step(to:b, by:0.5) {|x| (blok.call(x) < y)? (print '*') : (print'#')}); puts}
end

puts(calka(-2, 1) {|x| -x ** 2 - x + 10})
puts(wykres(-20,20) {|x| x<0? -x : x })


