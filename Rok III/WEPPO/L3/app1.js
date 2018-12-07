var obj = {
    name: "kettle",
    price: 20,
    value: function() {
        return 42;
    },
    mth: function() {
        return "str";
    },
    get product() {
        return this.name + " " + this.price;
    },
    set product( prod ) {
        x = prod.split(" ");
        this.name = x[0];
        this.price = x[1];
    }
}
//Dodawanie składowych
console.log(obj.var);
obj.var = 21;
console.log(obj.var);

console.log(obj.fun);
obj.fun = function() {return 666;}
console.log(obj.fun());
//nie dodam get set
console.log(Object.keys(obj));

//getter setter
console.log( obj.product );
obj.product = "pot 80";
console.log( obj.product ); 


Object.defineProperty( obj, 'x', {
    value: "abc",
    writable: false
});
Object.defineProperty( obj, 'function1', {
    value: function() {
        return 17;
    }
});
Object.defineProperty(obj, 'getset', {
        get: function() { 
            return this.price
        },
        set: function( newPrice ) { 
            this.price = newPrice
        }
    }
);

console.log( obj.function1() ); 
console.log( obj.x );
console.log( obj.getset );
obj.getset = 99;
console.log( obj.getset );
console.log( obj.price );


obj.x = "cba";
console.log( obj.x );