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

//Iter

var _it = fibIter();
for ( var _result; _result = _it.next(), !_result.done; ) {
    console.log( _result.value );
}

/*
var fooI = {
    [Symbol.iterator] : fibIter
};

for ( var i of fooI) {
    console.log( i );
}
*/

//Gen
/*
var _it = fibGen();
for ( var _result; _result = _it.next(), !_result.done; ) {
console.log( _result.value );
}
*/
/*
for ( var i of fibGen()) {
    console.log( i );
}
*/