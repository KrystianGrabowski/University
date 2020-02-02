function sum(...numbers) {
    var sum = 0;
    numbers.forEach(_ => sum += _);
    return sum;
}
    
console.log(sum(1,2,3));
// 6
console.log(sum(1,2,3,4,5));
// 15
console.log(sum(5,5,5,5,5,5,5,5,5,5,10,11));
//71
    