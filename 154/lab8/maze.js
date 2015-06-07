"use strict";

(function() {
  
  var wallWasHit = false;
  var startPressed = false;
  
  window.onload = function() {
    var walls = document.querySelectorAll(".boundary");
    for (var i = 0; i < walls.length; i++) {
      walls[i].onmouseover = turnRed;
    }
    var end = document.getElementById("end");
    end.onmouseover = win;
    var start = document.getElementById("start");
    start.onclick = reset;
    start.onmouseover = function() {
      startPressed = true;
    }
    var mazebody = document.getElementById("maze");
    mazebody.onmouseout = loseEverything;
  };
  
  function loseEverything() {
    if (startPressed) {
      turnRed();
      win();
    }
  }
  
  function turnRed() {
    var walls = document.querySelectorAll(".boundary");
    for (var i = 0; i < walls.length; i++) {
      walls[i].classList.add("youlose");
    }
    wallWasHit = true;
    win();
  }
  
  function win() {
    var status = document.getElementById("status");
    if (wallWasHit) {
      status.innerHTML = "You lost, loser";
    } else {
      status.innerHTML = "You won!";
    }
  }
  
  function reset() {
    startPressed = true;
    var walls = document.querySelectorAll(".boundary");
    for (var i = 0; i < walls.length; i++) {
      walls[i].classList.remove("youlose");
    }
    wallWasHit = false;
    document.getElementById("status").innerHTML = "Move your mouse over the \"S\" to begin."
  }
  
  
  
  
  
  
})();