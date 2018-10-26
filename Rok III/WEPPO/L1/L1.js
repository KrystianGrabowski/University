function task1_tester(x){
    var digits = x.toString()
    var sum = 0;
    for (let j=0; j<digits.length; j++){
        if(Number(digits[j]) == 0 || x % Number(digits[j]) != 0) {return false;}
        sum += Number(digits[j])
    }
    return (x % sum == 0)
}
function task1(){
    var arr = [];
    for (let i=1; i<=100000; i++){
        if (task1_tester(i)){
            arr.push(i);
        }
    }
    return arr;
} 

//console.log(task1().length);

function prime(x){
    for (let j=2; j<=Math.sqrt(x); j++){
        if (x % j == 0) {return false;}
    }
    return true;
}

function task2(){
    var arr = [];
    for (let i=2; i<=100000; i++){
        if (prime(i)){
            arr.push(i);
        }
    }
    return arr;
}
//console.log(task2());

//nast_wywolanie/nast_instrukcja/wejdz_do_fun/wyjdz_z_fun


function task5_rec(n){
    if (n==0) {return 0;}
    if (n==1) {return 1;}
    else {return task5_rec(n-1) + task5_rec(n-2); }
}   

function task5_iter(n){
    f0 = 0;
    f1 = 1;
    for (let i=2; i<=n; i++){
        x = f0;
        f0 = f1;
        f1 = x + f0;
    }
    return f1;
}

/*
for (let p=10; p<46; p++){
    console.log(p);
    console.time("iteration");
    task5_iter(p);
    console.timeEnd("iteration");
    console.time("recursion");
    task5_rec(p);
    console.timeEnd("recursion");
}
*/


//Node.js -> 44 11s (41>2s)
//Chrome -> 44 14s (40>2s)
//Mozilla ->41stop 106s (33>2s) (35>6s)