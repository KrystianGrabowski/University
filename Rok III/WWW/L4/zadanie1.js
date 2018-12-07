var my_div = document.createElement("div");
my_div.id = "menu";

function fun(x) {document.getElementById("menu").style.borderColor = x};

var a1 = document.createElement("a");
a1.setAttribute("href" ,"#");
a1.innerHTML = "Czerwony";
a1.setAttribute('onclick',"fun('red')");
var a2 = document.createElement("a");
a2.setAttribute("href" ,"#");
a2.innerHTML = "Czarny";
a2.setAttribute('onclick',"fun('black')");
var a3 = document.createElement("a");
a3.setAttribute("href" ,"#");
a3.innerHTML = "Brązowy";
a3.setAttribute('onclick',"fun('brown')");


//Chrome console

//Niesprecyzowane czy dodajemy do body czy content? 2 wersje:
//document.body.appendChild(my_div);
//document.getElementById("content").appendChild(my_div);


//my_div.style.border = "3px solid blue";

//document.getElementById('menu').appendChild(a1);
//document.getElementById('menu').appendChild(document.createElement("br"));
//document.getElementById('menu').appendChild(a2);
//document.getElementById('menu').appendChild(document.createElement("br"));
//document.getElementById('menu').appendChild(a3);

