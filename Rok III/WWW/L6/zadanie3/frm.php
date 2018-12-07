<!DOCTYPE html>
<html>
    <head>
        <title> frm </title>
    </head>

    <body>
        <form action="zadanie3.php" method="post">
            val1:<input type="text" name="a"/>
            val2:<input type="text" name="b"/>
            <input type="submit" value="submit">
        </form>
    </body>
</html>


<!--
    Content-Type: application/x-www-form-urlencoded
    accountType=HOSTED_OR_GOOGLE&Email=yourusername@gmail.com&Passwd=yourpassword&service=finance&source=test-test-.01
    
    a=1&b=2

    Content-Type: multipart/form-data; boundary=-------------------------acebdf13572468
    
---------------------------acebdf13572468
Content-Disposition: form-data; name="description" 

the_text_is_here
---------------------------acebdf13572468--

-->