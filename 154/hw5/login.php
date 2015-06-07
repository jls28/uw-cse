<?php
	//Stefan Dierauf May 2014
	//login form data handler for start.php for remember the cow
	
	
	//set the time zone for cookie creation
	date_default_timezone_set('America/Los_Angeles');
	
	$name = "";
	$password = "";
	
	//get the name
	if (isset($_POST["name"])) {
		$name = $_POST["name"];
	} else {
		header("Location: start.php?fail=name"); 
		die();
	}
	
	//get the password
	if (isset($_POST["password"])) {
		$password = $_POST["password"];
	} else {
		header("Location: start.php?fail=password");
		die();
	}
	
	//check if matches -> check if bad password
	//if not found, attempts to create a new account
	$logins = file("users.txt", FILE_IGNORE_NEW_LINES);
	foreach ($logins as $login) {
	//handle malformatted login?
		list($username, $storedpass) = explode(":", $login);
		if ($name == $username) {
			if ($storedpass == $password) {
				startsession($name, $password);
			} else {
				header("Location: start.php?fail=badpassword");
				die();
			}
		}
	}
	
	//$name and $password don't exist, so check for validness of pw and name
	if (preg_match("/^[a-z0-9]{3,8}$/", $name)) {
		if (preg_match("/^[0-9].{4,10}\W$/", $password) && !preg_match("/" . $name . "/", $password)) {
			file_put_contents("users.txt", implode(":", array($name, $password)) . "\n", FILE_APPEND);
			startsession($name, $password);
		} else {
			header("Location: start.php?fail=invalidpassword");
			die();
		}
	} else {
		header("Location: start.php?fail=invalidname");
		die();
	}
	
	//starts a session with the given name and password, and creates last login cookie
	//redirects to todolist.php
	function startsession($name, $password) {
  	session_start();
		$_SESSION["name"] = $name;
		$_SESSION["password"] = $password;
		setcookie("lastlogin", date("D y M d, g:i:s a"), time() + 60 * 60 * 24 * 7);
		header("Location: todolist.php");
	}

?>