//Stefan Dierauf May 2014
//javascript for the ascii animations web page
//reversing extra feature implemented

"use strict";

(function () {

  //GLOBALS!!!!!!!!!
  var currentAnimationData = "";
  var frameSpeed = 250;
  var frame = 0;
  var intervalId = "";
  var reversed = false;
  
  //bind to all elements, set up initial state
  window.onload = function() {
    var view = document.getElementById("view");
    var start = document.getElementById("startButton");
    var stop = document.getElementById("stopButton");
    var animationDropdown = document.getElementById("animation");
    var size = document.getElementById("size");
    var radios = document.querySelectorAll(".speedbuttons input");
    for (var i = 0; i < radios.length; i++) {
      radios[i].onclick = speedChanged;
    }
    var reverseBox = document.getElementById("reverse");
    reverseBox.onchange = reverse;
    
    start.onclick = startClick;
    stop.onclick = stopClick;
    animationDropdown.onchange = animationChanged;
    size.onchange = sizeChanged;
    stop.disabled = true;
    
    load("blank");
  };
  
  
  //Called when start is clicked
  //starts the animation and toggles correct buttons
  function startClick() {
    intervalId = setInterval(step, frameSpeed);
    toggleStart();
  }
  
  //toggles the start and stop buttons disabledness
  function toggleStart() {
     var start = document.getElementById("startButton");
     var stop = document.getElementById("stopButton");
     var animationDropdown = document.getElementById("animation");
     start.disabled = !start.disabled;
     stop.disabled = !stop.disabled;
     animationDropdown.disabled = !animationDropdown.disabled;
  }
  
  //stops the animation
  function stopClick() {
    clearInterval(intervalId);
    toggleStart();
  }
  
  //draws one frame of the animation and advances the current frame
  function step() {
    var view = document.getElementById("view");
    view.value = currentAnimationData[frame];
    if (reversed) {
      frame--;
    } else {
      frame++;
    }
    var m = currentAnimationData.length;
    frame =  ((frame % m) + m) % m; //stupid javascript mod implementation (-1 % 4 == -1, not 3)
  }
  
  //called when the animation dropdown is changed
  //changes the currently playing animation
  function animationChanged() {
    var animationDropdown = document.getElementById("animation");
    load(animationDropdown.value);
  }
  
  //loads the named animation into an array
  function load(animationName) {
    currentAnimationData = ANIMATIONS[animationName].split("=====\n");
    frame = 0;
    step();
  }
  
  //called when the size dropdown is changed
  //changes the size of the font in the textarea
  function sizeChanged() {
    var view = document.getElementById("view");
    var size = document.getElementById("size").value;
    view.style.fontSize = size; //includes pt
  }
  
  //called  when the speed radio buttons are changed
  //changes the frame rate of the animation
  function speedChanged() {
    var radios = document.querySelectorAll(".speedbuttons input");
    for (var i = 0; i < radios.length; i++) {
      if (radios[i].checked) {
        frameSpeed = radios[i].value;
        clearInterval(intervalId);
        if (document.getElementById("startButton").disabled) { //check if currently running
          intervalId = setInterval(step, frameSpeed);
        } 
      }
    }
  }
  
  //called when the reverse checkbox is changed
  //causes the animation to reverse direction
  function reverse() {
    reversed = document.getElementById("reverse").checked;
  }
  
})();
