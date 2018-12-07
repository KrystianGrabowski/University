$( function() {
    var dialog, form, 
      name = $( "#name" ),
      surname = $( "#surname" ),
      city = $( "#city" ),
      zipcode = $( "#zipcode" ),
      birthdate = $( "#birthdate" ),
      allFields = $( [] ).add( name ).add( surname ).add( city ).add( zipcode).add( birthdate ),
      tips = $( ".validateTips" );
 
    function updateTips( t ) {
      tips
        .text( t )
        .addClass( "ui-state-highlight" );
      setTimeout(function() {
        tips.removeClass( "ui-state-highlight", 1500 );
      }, 500 );
    }
 
    function checkLength( o, n, min, max ) {
      if ( o.val().length > max || o.val().length < min ) {
        o.addClass( "ui-state-error" );
        updateTips( "Długość " + n + " musi mieścić się pomiędzy " +
          min + " a " + max + "." );
        return false;
      } else {
        return true;
      }
    }
 
    function checkRegexp( o, regexp, n ) {
      if ( !( regexp.test( o.val() ) ) ) {
        o.addClass( "ui-state-error" );
        updateTips( n );
        return false;
      } else {
        return true;
      }
    }
 
    function addUser() {
      var valid = true;
      allFields.removeClass( "ui-state-error" );
 
      valid = valid && checkLength( name, "imienia", 3, 20 );
      valid = valid && checkLength( surname, "nazwiska", 3, 20 );
      valid = valid && checkLength( city, "miasta", 3, 20 );
      valid = valid && checkLength( zipcode, "kodu pocztowego", 6, 6 );
      valid = valid && checkLength( birthdate, "daty urodzenia", 10, 10 );
 
      valid = valid && checkRegexp( name, /^[A-ZĄĘŁŃÓŚŹŻ][a-ząćęłńóśźż]*$/, "Imię może zawierać tylko znaki a-z i zaczynać się wielką literą" );
      valid = valid && checkRegexp( surname, /^[A-ZĄĘŁŃÓŚŹŻ][a-ząćęłńóśźż]*$/, "Nazwisko może zawierać tylko znaki a-z i zaczynać się wielką literą" );
      valid = valid && checkRegexp( city, /^[A-ZĄĘŁŃÓŚŹŻ][a-ząćęłńóśźż]*$/, "Miasto może zawierać tylko znaki a-z i zaczynać się wielką literą" );
      valid = valid && checkRegexp( zipcode, /^[0-9]{2}-[0-9]{3}/, "Kod pocztowy musi zawieać pięć cyfr oddzielonych myślnikiem" );
      valid = valid && checkRegexp( birthdate, /^[0-9]{2}-[0-9]{2}-[1-2]{1}[0-9]{3}/, "Data urodzenia musi mieć postać dd-mm-yy" );
 
      if ( valid ) {
        $( "#users tbody" ).append( "<tr>" +
          "<td>" + name.val() + "</td>" +
          "<td>" + surname.val() + "</td>" +
          "<td>" + city.val() + "</td>" +
          "<td>" + zipcode.val() + "</td>" +
          "<td>" + birthdate.val() + "</td>" +
          "<td>" + "<button type='button'  class='removeuser' title='Usuń'>X</button>" + "</td>" +
        "</tr>" );
        dialog.dialog( "close" );
      }
      return valid;
    }
 
    dialog = $( "#dialog-form" ).dialog({
      autoOpen: false,
      height: 600,
      width: 400,
      modal: true,
      buttons: {
        "Create an account": addUser,
        Cancel: function() {
          dialog.dialog( "close" );
        }
      },
      close: function() {
        form[ 0 ].reset();
        allFields.removeClass( "ui-state-error" );
      }
    });

    $("#birthdate").datepicker({
        dateFormat: 'dd-mm-yy'
    });

    form = dialog.find( "form" ).on( "submit", function( event ) {
      event.preventDefault();
      addUser();
    });
 
    $( "#create-user" ).button().on( "click", function() {
      dialog.dialog( "open" );
    });

    $(document).on('click', 'button.removeuser', function () {
        rmv.dialog('open');
        $(this).closest('tr').addClass('toRemove');
        return false;
    });

    rmv = $("#dialog-remove").dialog({
        resizable: false,
        height: "auto",
        width: 400,
        modal: true,
        autoOpen: false,
        buttons: {
            "Tak": function () {
                $(".toRemove").remove();
                $(this).dialog("close");
            },
            "Nie": function () {
                $(".toRemove").removeClass("toRemove");
                $(this).dialog("close");
                
                
            }
        }
    });
      
  } );