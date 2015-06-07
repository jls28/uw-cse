/*
  Stefan Dierauf May 2014
  Game logic and other javascripty stuff for fifteen puzzle
  #winning extra feature implemented
*/

"use strict";

(function() {

  var OPEN_ROW = 3;
  var OPEN_COL = 3;
  
  //sets up the board
  window.onload = function() {
    freshBoard();
    var shuffleButton = document.getElementById("shufflebutton");
    shuffleButton.onclick = shuffle;
  };
  
  //returns a single 15 tile with the correct positioning based on number
  function makeTile(num) {
    var newTile = document.createElement("div");
    newTile.classList.add("tile");
    var row  = Math.floor((num - 1) / 4);
    var y = -row * 100;
    var col = ((num - 1) % 4) ; 
    var x = -col * 100 ;
    newTile.style.backgroundPosition = x + "px " + y + "px";
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
      newTile.onclick = tryMoveTile;
      puzzleArea.appendChild(newTile);
      place(newTile);
    }
  }
  
  //places a tile based on its row and column
  function place(tile) {
    tile.style.top = tile.row * 100 + "px";
    tile.style.left = tile.col * 100 + "px";
  }
  
  //changes tile appearance
  function tileHover() {
    console.log("hovering!");
    if (isNeigborToEmpty(this)) {
      this.classList.add("canMove");
      this.movable = true;
    }
  }
  
  //checks if the passed tile is a neighbor of the empty tile;
  function isNeigborToEmpty(tile) {
    return ((tile.col == OPEN_COL && tile.row == OPEN_ROW - 1) ||
    (tile.col == OPEN_COL && tile.row == OPEN_ROW + 1) ||
    (tile.row == OPEN_ROW && tile.col == OPEN_COL - 1) ||
    (tile.row == OPEN_ROW && tile.col == OPEN_COL + 1));
  }
  
  //Updates the appearance and movability of a tile that is no longer being hovered over
  function tileStopHover() {
    this.classList.remove("canMove");
    this.movable = false;
  }
  
  //Moves the tile if it's movable and checks if the game is won
  function tryMoveTile() {
    if (this.movable) {
      moveTile(this);
    }
    var win = document.getElementById("output");
    if (isCompleted()) {
      win.classList.add("winrar");
      win.innerHTML = "You WIN!";
    } else {
      win.classList.remove("winrar");
      win.innerHTML = "";
    }
  }
  
  //checks if the board is solved
  function isCompleted() {
    var tiles = document.querySelectorAll(".tile");
    for (var i = 0; i < tiles.length; i++) {
      var number = parseInt(tiles[i].innerHTML);
      if (!(tiles[i].col == ((number - 1) % 4) && tiles[i].row == Math.floor((number - 1)/ 4))) {
        return false;
      }
    }
    return true;
  }
  
  //Moves a tile and updates the OPEN_COL and OPEN_ROW
  function moveTile(tile) {
    var tempCol = tile.col;
    var tempRow = tile.row;
    tile.col = OPEN_COL;
    tile.row = OPEN_ROW;
    OPEN_COL = tempCol;
    OPEN_ROW = tempRow;
    place(tile);
  }
  
  //either marks all movable tiles or sets all tiles movable to false,
  //and returns an array of movable tiles
  function findMovable(start) {
    var tiles = document.querySelectorAll(".tile");
    var movableTiles = [];
    for (var i = 0; i < tiles.length; i++) {
      if (start) {
        if (isNeigborToEmpty(tiles[i])) {
          tiles[i].movable = true;
          movableTiles.push(tiles[i]);
        }
      } else {
        tiles[i].movable = false;
      } 
    }
    return movableTiles;
  }
  
  //Shuffles the tiles
  function shuffle() {
    for (var i = 0; i < 1000; i++) {
      var movableTiles = findMovable(true);
      var tileToMove = movableTiles[Math.floor((Math.random() * movableTiles.length))];
      moveTile(tileToMove);
      findMovable(false); //set movability all to false
    }
  }
})();