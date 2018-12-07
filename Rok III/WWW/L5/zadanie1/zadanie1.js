'use strict';

$(function() {
    $( "#slider-range-max" ).slider({
        range: "max",
        min: 1,
        max: 5,
        value: 2,
        slide: function( event, ui ) {
          pause = ui.value * 1000;
          $( "#amount" ).val( ui.value );
        },
        change: function(event, ui) { 
          pauseSlider();
          startSlider();
      }
    });
    
    $( "#amount" ).val( $( "#slider-range-max" ).slider( "value" ) );

    var width = 720;
    var animationSpeed = 1000;
    var pause = $('#slider-range-max').slider("value") * 1000;
    var currentSlide = 1;
    var $slider = $('#slider');
    var $slideContainer = $slider.find('.slides');
    var $slides = $slider.find('.slide');
    var interval;

    function startSlider() {
        interval = setInterval(function() {
            $slideContainer.animate({'margin-left': '-='+width}, animationSpeed, function() {
                if (++currentSlide === $slides.length) {
                    currentSlide = 1;
                    $slideContainer.css('margin-left', 0);
                    //$slideContainer.animate({'margin-left': 0}, animationSpeed);
                }
            });
        }, pause);
    }
    function pauseSlider() {
        clearInterval(interval);
    }

    $slideContainer
        .on('mouseenter', pauseSlider)
        .on('mouseleave', startSlider);

        
    startSlider();
});