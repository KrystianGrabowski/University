<!DOCTYPE html>
<html>
    <head>
        <title>
            Zadanie 2
        </title>
        <meta charset="UTF-8">

    </head>

    <body>
        <h1>Zadanie2</h1>
        
        <ul>
        <?php
        //POST
        print("POST"); 
        if(!empty($_POST)){
            foreach ($_POST as $key => $value) {
                echo "<li>$key : $value</li>";
            }     
        }       
        ?>
        </ul>
        <ul>

        <?php
        //GET
        print("GET");
        if(!empty($_GET)){
            foreach ($_GET as $key => $value) {
                echo "<li>$key : $value</li>";
            }     
        }
        ?>
        </ul>
        <?php
        print("REQUEST");
        print_r($_REQUEST);
        //print_r($_SERVER);
        ?>
        
        <br><br>
        <hr>
    </body>
</html>