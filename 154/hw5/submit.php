<?php
	//Stefan Dierauf May 2014
	//submit.php page for remember the cow
	//adds or removes stuff from the list
	//All CS Majors only features implemented


session_start();
$name = $_SESSION["name"];
$todolist = file("todo_" . $name . ".txt", FILE_IGNORE_NEW_LINES);

//delete an element unless its out of bounds
if ($_POST["action"] == "delete") {
  if ($_POST["index"] < count($todolist)) {
    unset($todolist[$_POST["index"]]);
  } else {
    header("Location: todolist.php?fail=outofbounds");
    die();
  }	
}

//add an element unless it's only white space
if ($_POST["action"] == "add") {
  if (!preg_match("/^\s*$/", $_POST["item"])) {
    array_push($todolist, $_POST["item"]);
  } else {
    header("Location: todolist.php?fail=invalid");
    die();
  }
}

$stringtoput = "";

foreach ($todolist as $item) {
	$stringtoput = $stringtoput . $item . "\n";
}

file_put_contents("todo_" . $name . ".txt", $stringtoput);

header("Location: todolist.php");

?>
