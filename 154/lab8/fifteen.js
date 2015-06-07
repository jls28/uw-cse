"use strict";

(function() {

  var openRow = 3;
  var openCol = 3;
  
  window.onload = function() {
    freshBoard();
    
  }
  
  
  //returns a single 15 tile with the correct positioning based on number
  function makeTile(num) {
    var newTile = document.createElement("div");
    newTile.classList.add("tile");
    //rows are /4, cols are %4 - 1
    var row  = Math.floor((num - 1) / 4);
    var y = -row * 100;
    var col = ((num - 1) % 4) ; 
    var x = -col * 100 ;
    newTile.style.backgroundPositionX = x + "px";
    newTile.style.backgroundPositionY = y + "px";
    newTile.innerHTML = num;
    newTile.row = row;
    newTile.col = col;
    newTile.movable = false;
    return newTile;
  }
  
  //makes a new 15 board
  function freshBoard() {
    var puzzleArea = document.getElementById("puzzlearea");
    for (var i = 1; i <= 15; i++) {
      var newTile = makeTile(i);
      newTile.onmouseover = tileHover;
      newTile.onmouseout = tileStopHover;
      newTile.onclick = moveTile;
      puzzleArea.appendChild(newTile);
      place(newTile);
    }
    console.log("fresh board made!");
  }
  
  //places a tile based on its row and column
  function place(tile) {
    tile.style.top = tile.row * 100 + "px";
    tile.style.left = tile.col * 100 + "px";
  }
  
  //changes tile appearance
  function tileHover() {
    console.log("hovering!");
  //if empty = 3, 3
  //then 2, 3 or 3, 2
  //if 2, 2
  //then 2, 1 v 1, 2 v 3, 2 v 2, 3
    if (isNeigborToEmpty(this)) {
      this.classList.add("canMove");
      this.movable = true;
    }
  }
  
  //checks if the passed tile is a neighbor of the empty tile;
  function isNeigborToEmpty(tile) {
    return ((tile.col == openCol && tile.row == openRow - 1) ||
    (tile.col == openCol && tile.row == openRow + 1) ||
    (tile.row == openRow && tile.col == openCol - 1) ||
    (tile.row == openRow && tile.col == openCol + 1));
  }
  
  function tileStopHover() {
    this.classList.remove("canMove");
    console.log("stopped hovering!");
    this.movable = false;
  }
  
  function moveTile() {
    if (this.movable) {
      var tempCol = this.col;
      var tempRow = this.row;
      this.col = openCol;
      this.row = openRow;
      openCol = tempCol;
      openRow = tempRow;
      place(this);
    } else {
      console.log("cant move it!");
    }
  }
  
  function setMovable() {
    var tiles = document.querySelectorAll(".tile ")
  }
    
  function shuffle {
    for (var i = 0; i < 1000; i++) {
      setMovable();
    }
  }
  
  
  
  
})();