function fib(n){
    if (n==0) {return 0;}
    if (n==1) {return 1;}
    else {return fib(n-1) + fib(n-2); }
}

var fibMemo = function() {
    var cache = [0, 1];
    return f = function(n) {
        if ( typeof cache[n] !== 'undefined') { //= null , no cast
            return cache[n];
        } else {
            var result = f(n-1) + f(n-2);
            cache[n] = result;
            return result;
        }
    }
}();
console.log(undefined == null);
for (let p=1; p<45; p++){
    console.log(p)
    console.time("old");
    fib(p);
    console.timeEnd("old");
    console.time("new");
    fibMemo(p);
    console.timeEnd("new");
}
//for (let p=1; p<66; p++){
//    console.log(p)
//    console.time("new");
//    console.log(fibMemo(p));
//    console.timeEnd("new");
//}

