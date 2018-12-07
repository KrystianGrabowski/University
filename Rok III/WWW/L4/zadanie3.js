window.onload = function load(){
    document.getElementById('main').onmouseover = MouseOver;
    document.getElementById('main').onmouseout  = MouseOut;
    document.getElementById('timer').onclick  = Placesquares;
}

var p = 0;
var punishment = 0.0;
var onboard = false;
var size = 0;
var squares = [];
var visitMain = true;
var gameOn = false;

function NewGrame(){
    span = document.createElement("span");
    span.textContent = "Czas: " + (p/1000) + "s + " + "kara " +punishment + "s" + " = " + (parseFloat(document.getElementById("stoper").textContent) + punishment) + 's';
    document.getElementById("timer").appendChild(document.createElement("br"));
    document.getElementById("timer").appendChild(span);
    NewValues();
    Placesquares();
}

function NewValues(){
    p = 0;
    onboard = true;
    size = 0;
    visitMain = true;
    gameOn = false;
    punishment = 0;
}

function SquareUndoError(el){
    el.style.backgroundColor = "green";
}

function SquareClick(){
    if (!gameOn || (visitMain && this.style.backgroundColor != "green") ){
        return false;
    }
    if (visitMain && this.style.backgroundColor == "green" ){
        punishment += 3.0;
    }
    else if (this.style.backgroundColor != "green"){
        this.style.backgroundColor = "green";
        size++;
        visitMain = true;
    }
    else{
        punishment += 3.0;
    }
    if (size == 28){
        NewGrame();
    }
}


function Placesquares(){
    NewValues();
    if (squares.length != 0){
        for (let x = 0; x < 28; x++){
            squares[x].parentNode.removeChild(squares[x]);
        }
    squares = [];
    }

    for (let x = 0; x< 1000; x+=100){
        for (let y = 0; y < 600; y+=200){
            if(!((x == 400 || x == 500) && y == 200)){
                my_div = document.createElement("div");
                my_div.style.position = "absolute";
                my_div.style.height = "30px";
                my_div.style.width = "30px";
                my_div.style.backgroundColor = "red";
                var a = x + Math.floor(Math.random() * 70);
                var b = y + Math.floor(Math.random() * 170);
                my_div.style.left = a + "px";
                my_div.style.top = b + "px";
                my_div.addEventListener("mouseover", SquareClick);
                document.getElementById("gamearea").appendChild(my_div);
                squares.push(my_div);
            }
        }
    }
    Math.floor(Math.random() * 10);
}

function MouseOver(){
    onboard = true;
    document.body.style.backgroundColor = "red";

}
function AddTime(){
    if (!onboard){
        p += 100;
        document.getElementById("stoper").textContent= (p/1000).toString() + " + " + punishment.toString();
        setTimeout(function(){AddTime()}, 100);
    }
}

function MouseOut(elClass){
    gameOn = true;
    visitMain = false;
    onboard = false;
    document.getElementById("stoper").textContent=p;
    document.body.style.backgroundColor = "black";
    setTimeout(function(){AddTime()}, 100);
}