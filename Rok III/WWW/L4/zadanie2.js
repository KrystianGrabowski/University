window.onload = function load(){
    document.getElementById('form').onsubmit = main_check;
    document.getElementById('numerkonta').onblur= nr_check;
    document.getElementById('pesel').onblur= pesel_check;
    document.getElementById('data').onblur= date_check;
	document.getElementById('email').onblur= email_check;
}

function checkout(rx, el){
    if (!rx.test(el.value)){
        el.style.border = "2px solid red";
        return false;
    }
    else{
        el.style.border = "1px solid green";
        return true;
    }
}

function main_check(){
    if (nr_check() && pesel_check() && date_check() && email_check()){
        alert("Sukces");
    }
    else{
        alert("Wyprowadzono błędne dane!");
    }
}

function nr_check(){
    var nr = document.getElementById("numerkonta");
    var rx = /^[0-9]{26}$/;
    return checkout(rx, nr);
}

function pesel_check(){
    var pesel = document.getElementById("pesel");
    var rx = /^[0-9]{11}$/;
    return checkout(rx, pesel);
    
}

function date_check(){
    var date = document.getElementById("data");
    var rx = /^([1-9]|[12]\d|3[01])\-([2-9]|1[0-2]?)\-[0-9]{4}$/;
    return checkout(rx, date);
    
}

function email_check(){
    var email = document.getElementById("email");
    var rx = /^[0-9a-zA-Z_.-]+@[0-9a-zA-Z.-]+[a-zA-Z]{2,3}$/
    return checkout(rx, email);
}
