function fibIter() {
    var fib0 = 0;
    var fib1 = 1;
    return {
        next : function() {
            var temp = fib0;
            fib0 = fib1;
            fib1 = fib0 + temp;
            return {
                value : temp,
                done : false
            }
        }
    }
}

function *fibGen() {
    var fib0 = 0;
    var fib1 = 1;
    while (true){
        var temp = fib0;
        fib0 = fib1;
        fib1 = fib0 + temp;
        yield temp
    }
}

function* take(it, top) {
    var num = 0;
    while (num < top){
        i = it.next()
        num++;
        yield i.value
    }
}

    // zwróć dokładnie 10 wartości z potencjalnie
    // "nieskończonego" iteratora/generatora
for (let num of take( fibGen(), 10 ) ) {
    console.log(num);
}
console.log("---------");
for (let num of take( fibGen(), 10 ) ) {
    console.log(num);
}
    