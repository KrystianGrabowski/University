/*function createGenerator() {
    var _state = 0;
    return {
        next : function() {
            return {
                value : _state,
                done : _state++ >= 10
            }
        }
    }
}*/

function createGenerator(start, end) {
    var _state = start;
    return {
        next : function() {
            return {
                value : _state,
                done : _state++ >= end
            }
        }
    }
}


var foo = {
    [Symbol.iterator] : createGenerator.bind(this, 0, 10)
};

var foo1 = {
    [Symbol.iterator] : createGenerator.bind(this, 65, 71)
};

var foo2 = {
    [Symbol.iterator] : createGenerator.bind(this, 11, 20)
};

for (var f of foo)
    console.log(f);
console.log("---------");
for (var f of foo1)
    console.log(f);
console.log("---------");
for (var f of foo2)
    console.log(f);












    

function createGenerato(start, end) {
    var _state = start;
    return function(){
        return {
        next : function() {
            return {
                 value : _state,
                 done : _state++ >= end
            }
        }
    }
    }
}

var fo = {
    [Symbol.iterator] : createGenerato( 0, 10)
};

var fo1 = {
    [Symbol.iterator] : createGenerato (65, 71)
};

var fo2 = {
    [Symbol.iterator] : createGenerato (11, 20)
};

for (var f of fo)
    console.log(f);
console.log("---------");
for (var f of fo1)
    console.log(f);
console.log("---------");
for (var f of fo2)
    console.log(f);