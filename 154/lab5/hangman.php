<?php
print $_GET["guess"];

$MAX_GUESSES  = 6;                           # max guesses that can be made before game ends
if (isset($_COOKIE["myguesses"])) {
	$guesses = $_COOKIE["myguesses"] - 1;
	if ($guesses < 0) {
		$guesses = $MAX_GUESSES;
	}
	setcookie("myguesses", $guesses);
} else {
	$guesses = $MAX_GUESSES;
	
}

$available = "abcdefghijklmnopqrstuvwxyz";   # letters available to be guessed

if (isset($_COOKIE["available"])) {
	$available = $_COOKIE["available"];
}

$newavailable = preg_replace("/" . $_GET["guess"] . "/", " ", $available);
if ($newavailable == $available) {
	$guesses += 1;
}
if ($guesses < 0) {
	$newavailable = "abcdefghijklmonpqrstuvwxyz";
}
setcookie("available", $newavailable);



# pick a random word from the dictionary file
$words = file("/www/html/cse154/labs/5/words.txt", FILE_IGNORE_NEW_LINES);
$word = "";
if (isset($_COOKIE["myword"])) {
	$word = $_COOKIE["myword"];
} else {
	$word = $words[rand(0, count($words))];
	setcookie("myword", $word);
}

setcookie("myguesses", $guesses);
$clue = "";
if (isset($_COOKIE["clue"])) {
	$clue = $_COOKIE["clue"];
} else {
	$clue = preg_replace("/./" , "?", $word);
	setcookie("clue", $clue);
}
?>

<!DOCTYPE html>
<html>
  <head>
    <title>Hangman</title>
    <link href="https://webster.cs.washington.edu/cse154/labs/5/hangman.css" type="text/css" rel="stylesheet" />
  </head>
  
  <body>
    <h1>Hangman Step by Step</h1>
    
    <div>
      <img src="https://webster.cs.washington.edu/cse154/labs/5/hangman<?= $guesses ?>.gif" alt="hangman" /> <br />
      (<?= $guesses ?> guesses remaining)
    </div>
    
    <div id="clue"> <?= $clue ?> </div>
    
		<form action="hangman.php">
			<input name="guess" type="text" size="1" maxlength="1" autofocus="autofocus" />
			<input type="submit" value="Guess" />
		</form>
    
		<form action="hangman.php" method="post">
			<input name="newgame" type="hidden" value="true" />
			<input type="submit" value="New Game" />
		</form>

    <div id="hint">
    	HINT: The word is: <code>"<?= $word ?>"</code> <br />
    	The letters available are: <code>"<?= $available ?>"</code>
    </div>
  </body>
</html>
