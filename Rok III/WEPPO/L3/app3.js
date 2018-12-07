function forEach( a, f ) {
    for (var i=0; i < a.length; i++){
        f(a[i]);
    }
}
function map( a, f ) {
    var result = [];
    for (var i=0; i < a.length; i++){
        result[i] = f(a[i]);
    }
    return result;
}
function filter( a, f ) {
    var result = [];
    for (var i=0; i < a.length; i++){
        if (f(a[i])){
            result.push(a[i]); 
        }
    }
    return result;
}
var a = [1,2,3,4];

forEach( a, _ => { console.log( _ ); } );
    // [1,2,3,4]
console.log(filter( a, _ => _ < 3 ));
    // [1,2]
console.log(map( a, _ => _ * 2 ));
    // [2,4,6,8]

forEach( a, function(x) {console.log(x)} );
    // [1,2,3,4]
console.log(filter( a, function(x) {return x < 3} ));
    // [1,2]
console.log(map( a, function(x) {return x * 2}));
    // [2,4,6,8]


    